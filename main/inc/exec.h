#ifndef _EXEC_H_
#define _EXEC_H_

#include "scan_defines.h"
#include "port_defines.h"
#include "argument_parser_types.h"
#include "protocol_ip.h"
#include "protocol_tcp.h"
#include "protocol_udp.h"
#include "scan_context.h"

void display_help(void);
void display_nopriv(void);
void display_version(void);

int single_thread_exec(const char *target_ip, argparse_port_set_t ports, scan_bitmap_t scans, scan_result_t results[RESULTS_CAPACITY]);
int16_t tcp_packet_create(uint8_t *buffer, uint32_t buffer_len, const protocol_ip_header_t *ip_header, const protocol_tcp_header_t *tcp_header, const uint32_t *payload, uint16_t payload_len);
int16_t udp_packet_create(uint8_t *buffer, uint32_t buffer_len, const protocol_ip_header_t *ip_header, const protocol_udp_header_t *udp_header, const uint32_t *payload, uint16_t payload_len);



#endif /* _EXEC_H_ */