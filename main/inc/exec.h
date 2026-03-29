#ifndef _EXEC_H_
#define _EXEC_H_

#include "nmap_types.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"

void display_help(void);

int single_thread_exec(const char *target_ip, port_bitmap_t ports, scan_bitmap_t scans);
int16_t tcp_packet_create(uint8_t *buffer, uint32_t buffer_len, const ip_header_t *ip_header, const tcp_header_t *tcp_header, const uint32_t *payload, uint16_t payload_len);
int16_t udp_packet_create(uint8_t *buffer, uint32_t buffer_len, const ip_header_t *ip_header, const udp_header_t *udp_header, const uint32_t *payload, uint16_t payload_len);



#endif /* _EXEC_H_ */