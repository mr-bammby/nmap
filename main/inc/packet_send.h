#ifndef _PACKET_SEND_H_
#define _PACKET_SEND_H_

#include "nmap_types.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"

void send_packet(int sockfd, const char *target_ip, int port, const char *local_ip, uint8_t scan_type, uint8_t udp_probe_variant);



#endif /* _PACKET_SEND_H_ */