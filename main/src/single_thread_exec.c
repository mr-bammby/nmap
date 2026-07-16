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
#include "scan_parser.h"
#include "protocol_utils.h"
#include "result_printer.h"
#include "sender.h"
#include "receiver.h"


#define NUMBER_OF_SCAN_TYPES SCAN_NUMBER_OF_SCAN_TYPES
#define RESPONSE_WAIT_ATTEMPTS 500
#define RESPONSE_POLL_SLEEP_US 1000



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
    pcap_t *pcap_handle = NULL;
    int sock = -1;
    char *local_ip;
    uint32_t link_header_len;
    argparse_port_set_iterator_t port_it;
    unsigned int port_i;

    argparse_port_iterator_init(&port_it, &ports);
    // Initialize results array
    protocol_utils_initialize_results(results);
    // Initialize sender socket
    if (sender_init(&sock) < 0)
    {
        LOGE("Failed to initialize sender socket\n");
        return -1;
    }
    // Initialize receiver
    if (receiver_init(target_ip, &port_it, &pcap_handle, &local_ip, &link_header_len) < 0)
    {
        LOGE("Failed to initialize receiver\n");

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
                response_slot = response_slot_for_scan(&results[port_i - 1], scan_flag);
                if (response_slot == NULL)
                {
                    LOGD("Done for port %d.\n", port_i);
                    continue;
                }
                *response_slot = RESPONSE_NO_RESPONSE;
                int max_attempts = RESPONSE_WAIT_ATTEMPTS;
                if (scan_flag == SCAN_FLG_UDP)
                    max_attempts = RESPONSE_WAIT_ATTEMPTS * PROTOCOL_UDP_TOTAL_PROBES;

                for (int attempt = 0; attempt < max_attempts; attempt++)
                {
                    sender_run(sock, target_ip, port_i, local_ip, scan_flag, attempt, response_slot);
                    // Wait in 1ms polls; UDP may span multiple windows via retries.
                    usleep(RESPONSE_POLL_SLEEP_US);
                    if(receiver_run(pcap_handle, link_header_len, response_slot, results) == 1)
                    {
                        break;
                    }
                }
                LOGD("Done for port %d.\n", port_i);
            }
        }
    }
    receiver_cleanup(pcap_handle);
    sender_cleanup(&sock);

    return 0;
}