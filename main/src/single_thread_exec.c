#define MODULE_DEBUG DEBUG_SINGLE_THREAD_EXEC
#include "debug.h"
#include <pcap.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "port_defines.h"
#include "scan_defines.h"
#include "scan_context.h"
#include "argument_parser.h"
#include "argument_parser_port.h"
#include "port_map.h"
#include "packet_handler.h"
#include "protocol_utils.h"
#include "result_printer.h"
#include "sender.h"
#include "receiver.h"
#include "timer_utils.h"
#include "exec.h"


#define NUMBER_OF_SCAN_TYPES SCAN_NUMBER_OF_SCAN_TYPES
#define RESPONSE_POLL_TIMEOUT_TCP_US 100
#define RESPONSE_POLL_TIMEOUT_UDP_US 1000
#define RESPONSE_POLL_SLEEP_US_LOCAL 10 /* Local override renamed to avoid redefinition with main/inc/sender.h */
#define RESPONSE_FINAL_WAIT_US 100000

struct nmap_single_thread_allocs
{
    int sender_socket;
    pcap_t *pcap_handle;
    char *local_ip;
};

struct nmap_single_thread_allocs g_single_thread_allocs = { -1, NULL, NULL };

void single_thread_cleanup(void)
{
    if (g_single_thread_allocs.pcap_handle != NULL)
    {
        receiver_cleanup(g_single_thread_allocs.pcap_handle);
        g_single_thread_allocs.pcap_handle = NULL;
    }
    sender_cleanup(&g_single_thread_allocs.sender_socket);
    if (g_single_thread_allocs.local_ip != NULL)
    {
        free(g_single_thread_allocs.local_ip);
        g_single_thread_allocs.local_ip = NULL;
    }
}

static response_type_t *response_slot_for_scan(scan_result_t *result, uint8_t scan_flag)
{
    if (scan_flag == SCAN_FLG_SYN)
        return &result->response_syn;
    if (scan_flag == SCAN_FLG_ACK)
        return &result->response_ack;
    if (scan_flag == SCAN_FLG_NULL)
        return &result->response_null;
    if (scan_flag == SCAN_FLG_FIN)
        return &result->response_fin;
    if (scan_flag == SCAN_FLG_XMAS)
        return &result->response_xmas;
    if (scan_flag == SCAN_FLG_UDP)
        return &result->response_udp;
    return NULL;
}

int single_thread_exec(const char *target_ip, argparse_port_set_t ports, scan_bitmap_t scans, scan_result_t results[RESULTS_CAPACITY])
{
    uint32_t link_header_len;
    argparse_port_set_iterator_t port_it;
    unsigned int port_i;
    nmap_timeout_t timeout;
    uint32_t receive_cnt = 0;
    uint32_t send_cnt = 0;

    timeout_init(&timeout, 0, 0);

    argparse_port_iterator_init(&port_it, &ports);
    // Initialize results array
    protocol_utils_initialize_results(results, &ports);
    // Initialize sender socket
    if (sender_init(&g_single_thread_allocs.sender_socket) < 0)
    {
        LOGE("Failed to initialize sender socket\n");
        single_thread_cleanup();
        return -1;
    }

    uint32_t target_addr;
    if (inet_pton(AF_INET, target_ip, &target_addr) != 1)
    {
        LOGE("Invalid target IP: %s\n", target_ip);
        single_thread_cleanup();
        return -1;
    }
    if (atomic_load(&interrupt_flag))
    {
        LOGE("Interrupt signal received before starting execution\n");
        single_thread_cleanup();
        return -1;
    }
    // Initialize receiver
    if (receiver_init(target_ip, &port_it, &g_single_thread_allocs.pcap_handle, &g_single_thread_allocs.local_ip, &link_header_len) < 0)
    {
        LOGE("Failed to initialize receiver\n");
        single_thread_cleanup();
        return -1;
    }
    if (atomic_load(&interrupt_flag))
    {
        LOGE("Interrupt signal received before starting execution\n");
        single_thread_cleanup();
        return -1;
    }
    while (argparse_port_iterator_next(&port_it, &port_i) == 0)
    {
        for (int scan_i = 0; scan_i < NUMBER_OF_SCAN_TYPES; scan_i++)
        {
            if (scans & (1 << scan_i))
            {
                uint8_t scan_flag = (uint8_t)(1u << scan_i);
                response_type_t *response_slot;
                LOGD("Scanning port %d with scan type %s...\n", port_i, scan_valid_tokens[scan_i]);
                int port_index = -1;
                if (argparse_port_find(&ports, port_i, &port_index) != 0)
                {
                    LOGD("Port %u not in active scan set.\n", port_i);
                    continue;
                }

                response_slot = response_slot_for_scan(&results[port_index], scan_flag);
                if (response_slot == NULL)
                {
                    LOGD("Done for port %d.\n", port_i);
                    continue;
                }
                *response_slot = RESPONSE_NO_RESPONSE;
                for (int probe = 0; probe < ((scan_flag == SCAN_FLG_UDP) ? PROTOCOL_UDP_TOTAL_PROBES : 1); probe++)
                {
                    uint8_t done = 0;
                    uint32_t local_ip = inet_addr(g_single_thread_allocs.local_ip);
                    sender_run(g_single_thread_allocs.sender_socket, target_addr, port_i, local_ip, scan_flag, probe, response_slot);
                    send_cnt++;
                    (scan_flag == SCAN_FLG_UDP) ? timeout_start(&timeout, RESPONSE_POLL_TIMEOUT_UDP_US) : timeout_start(&timeout, RESPONSE_POLL_TIMEOUT_TCP_US);
                    while (1)
                    {
                        if (atomic_load(&interrupt_flag))
                        {
                            LOGE("Interrupt signal received before starting execution\n");
                            single_thread_cleanup();
                            return -1;
                        }
                        if (timeout_check(&timeout))
                        {
                            break;
                        }
                        if(receiver_run(g_single_thread_allocs.pcap_handle, link_header_len, response_slot, results, &ports) == 1)
                        {
                            done = 1;
                            receive_cnt++;
                            break;
                        }
                        usleep(RESPONSE_POLL_SLEEP_US_LOCAL);
                    }
                    if (done)
                    {
                        break;
                    }
                }
                LOGD("Done for port %d.\n", port_i);
            }
        }
    }
    /* Allow some extra time to collect any late responses before tearing down */
    LOGD("Polling for late responses for %u us before cleanup, receive cnt %u, send cnt %u\n", (unsigned)RESPONSE_FINAL_WAIT_US, (unsigned)receive_cnt, (unsigned)send_cnt);
    if (receive_cnt < send_cnt)
    {
        unsigned int waited_us = 0;
        /* Poll receiver_run repeatedly so packets arriving during this window are processed. */
        while (waited_us < RESPONSE_FINAL_WAIT_US)
        {
            response_type_t dummy_response = RESPONSE_NO_RESPONSE;
            if(receiver_run(g_single_thread_allocs.pcap_handle, link_header_len, &dummy_response, results, &ports) == 1)
            {
                receive_cnt++;
            }
            if (receive_cnt >= send_cnt)
            {
                LOGD("All sent probes have received responses, exiting final polling early\n");
                break;
            }
            if (atomic_load(&interrupt_flag))
            {
                LOGE("Interrupt signal received during final response polling\n");
                single_thread_cleanup();
                return -1;
            }
            usleep(RESPONSE_POLL_SLEEP_US_LOCAL);
            waited_us += RESPONSE_POLL_SLEEP_US_LOCAL;
        }
    }
    single_thread_cleanup();
    return 0;
}