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
#include "timer_utils.h"
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

int single_thread_exec(const char *target_ip, argparse_port_set_t ports, scan_bitmap_t scans)
{
    pcap_t *pcap_handle = NULL;
    int sock = -1;
    char *local_ip;
    uint32_t link_header_len;
    scan_result_t results[RESULTS_CAPACITY];
    nmap_timer_t timer;
    float elapsed_time;
    argparse_port_set_iterator_t port_it;
    unsigned int port_i;

    argparse_port_iterator_init(&port_it, &ports);

    // Initialize results array
    initialize_results(results);

    // Initialize sender socket
    if (sender_init(&sock) < 0)
    {
        LOGE("Failed to initialize sender socket\n");
        return -1;
    }

    // Initialize receiver
    if (receiver_init(target_ip, scans, &port_it, &pcap_handle, &local_ip, &link_header_len) < 0)
    {
        LOGE("Failed to initialize receiver\n");

        return -1;
    }
    
    start_timer(&timer);
    while (argparse_port_iterator_next(&port_it, &port_i) == 0)
    {
        for (int scan_i = 0; scan_i < NUMBER_OF_SCAN_TYPES; scan_i++)
        {
            if (scans & (1 << scan_i))
            {
                uint8_t scan_flag = (uint8_t)(1u << scan_i);
                response_type_t *response_slot;
                LOGD("Scanning port %d with scan type %s...\n", port_i, scan_valid_tokens[scan_i]);
                send_packet(sock, target_ip, port_i, local_ip, scan_flag, 0);
                response_slot = response_slot_for_scan(&results[port_i - 1], scan_flag);
                if (response_slot == NULL)
                {
                    LOGD("Done for port %d.\n", port_i);
                    continue;
                }

                *response_slot = RESPONSE_NO_RESPONSE;

                int max_attempts = RESPONSE_WAIT_ATTEMPTS;
                if (scan_flag == SCAN_FLG_UDP)
                    max_attempts = RESPONSE_WAIT_ATTEMPTS * UDP_TOTAL_PROBES;

                for (int attempt = 0; attempt < max_attempts; attempt++)
                {
                    if (scan_flag == SCAN_FLG_UDP &&
                        attempt > 0 &&
                        (attempt % RESPONSE_WAIT_ATTEMPTS) == 0 &&
                        *response_slot == RESPONSE_NO_RESPONSE)
                    {
                        uint8_t udp_probe_variant = (uint8_t)(attempt / RESPONSE_WAIT_ATTEMPTS);
                        send_packet(sock, target_ip, port_i, local_ip, scan_flag, udp_probe_variant);
                    }

                    // Wait in 1ms polls; UDP may span multiple windows via retries.
                    usleep(RESPONSE_POLL_SLEEP_US);

                    struct pcap_pkthdr *header;
                    const unsigned char *packet;
                    int res = pcap_next_ex(pcap_handle, &header, &packet);
                    if (res == 1)
                    {
                        LOGD("PACKET PROCESSING\n");
                        process_packet(packet, header->caplen, link_header_len, results);
                        /* Only stop when this specific probe got a conclusive response. */
                        if (*response_slot != RESPONSE_NO_RESPONSE)
                            break;
                    }
                }
                LOGD("Done for port %d.\n", port_i);
            }
        }
    }
    stop_timer(&timer);
    elapsed_time = read_time_s(&timer);
    parse_scan_results(results, PORT_START - 1, PORT_END, target_ip, elapsed_time);
    receiver_cleanup(pcap_handle);
    sender_cleanup(&sock);
    close(sock);

    return 0;
}