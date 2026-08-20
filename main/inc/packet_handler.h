#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include <stdint.h>
#include "protocol_ip.h"
#include "protocol_tcp.h"
#include "protocol_udp.h"
#include "argument_parser_types.h"
#include "multi_thread_shared_res.h"
#include "argument_parser_types.h"

/* Sends IP packets to target ip depending on the scan type, probe and port. */
void send_packet_ip(int sockfd, uint32_t target_ip, int port, uint32_t local_ip, uint8_t scan_type, uint8_t udp_probe_variant);

/* Processes incoming packets and updates scan results. */
int8_t process_packet(const unsigned char *packet, uint32_t packet_len, uint32_t link_header_len, scan_result_t *results, const argparse_port_set_t *ports);

/* Processes incoming packets in a multi-threaded environment and updates scan results. */
int8_t multi_thread_process_packet(const unsigned char *packet, uint32_t packet_len, uint32_t link_header_len, scan_result_t **results, addr_hashmap_t *hash_map, const argparse_port_set_t *ports);

#endif /* PACKET_HANDLER_H */