#ifndef PACKET_SEND_H
#define PACKET_SEND_H

#include <stdint.h>
#include "protocol_ip.h"
#include "protocol_tcp.h"
#include "protocol_udp.h"
#include "argument_parser_types.h"
#include "multi_thread_shared.h"
#include "argument_parser_types.h"


void send_packet_ip(int sockfd, uint32_t target_ip, int port, uint32_t local_ip, uint8_t scan_type, uint8_t udp_probe_variant);
int8_t process_packet(const unsigned char *packet, uint32_t packet_len, uint32_t link_header_len, scan_result_t *results, const argparse_port_set_t *ports);

int8_t multi_thread_process_packet(const unsigned char *packet, uint32_t packet_len, uint32_t link_header_len, scan_result_t **results, addr_hashmap_t *hash_map, const argparse_port_set_t *ports);

#endif /* PACKET_SEND_H */