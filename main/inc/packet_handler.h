#ifndef PACKET_SEND_H
#define PACKET_SEND_H

#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "argument_parser_types.h"

void send_packet(int sockfd, const char *target_ip, int port, const char *local_ip, uint8_t scan_type, uint8_t udp_probe_variant);
int8_t process_packet(const unsigned char *packet, uint32_t packet_len, uint32_t link_header_len, scan_result_t *results);



#endif /* PACKET_SEND_H */