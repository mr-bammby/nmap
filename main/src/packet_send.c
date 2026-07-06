#define MODULE_DEBUG DEBUG_PACKET_SEND
#include "debug.h"
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "scan_defines.h"
#include "protocol_ip.h"
#include "protocol_tcp.h"
#include "protocol_utils.h"
#include "protocol_udp.h"
#include "port_map.h"
#include "exec.h"
#include "scan_context.h"


#define MIN_SRC_PORT 1024
#define MAX_SRC_PORT PORT_MAX_PORT

#define COOKIE_MAKE(scan_id, port) \
    ((COOKIE_MAGIC << 20) | (((uint32_t)(scan_id) & 0xF) << 16) | ((port) & 0xFFFF))


static int8_t set_scan_type_flag(protocol_ip_header_t *ip_hdr, protocol_tcp_header_t *tcp_hdr, uint8_t scan_type)
{
    int8_t ret = 0;

    switch (scan_type)
    {
        case SCAN_FLG_SYN:
            ip_hdr->protocol = IPPROTO_TCP;
            tcp_hdr->flags = PROTOCOL_TCP_FLAG_SYN;
            break;
        case SCAN_FLG_ACK:
            ip_hdr->protocol = IPPROTO_TCP;
            tcp_hdr->flags = PROTOCOL_TCP_FLAG_ACK;
            break;
        case SCAN_FLG_NULL:
            ip_hdr->protocol = IPPROTO_TCP;
            tcp_hdr->flags = 0;
            break;
        case SCAN_FLG_FIN:
            ip_hdr->protocol = IPPROTO_TCP;
            tcp_hdr->flags = PROTOCOL_TCP_FLAG_FIN;
            break;
        case SCAN_FLG_XMAS:
            ip_hdr->protocol = IPPROTO_TCP;
            tcp_hdr->flags = PROTOCOL_TCP_FLAG_FIN | PROTOCOL_TCP_FLAG_PSH | PROTOCOL_TCP_FLAG_URG;
            break;
        case SCAN_FLG_UDP:
            ip_hdr->protocol = IPPROTO_UDP;
            break;
        default:
            perror("Unsupported scan type");
            ret = -1;
            break;
    }
    return ret;
}

static int16_t udp_send_packet(uint8_t *packet, uint32_t packet_len, protocol_ip_header_t *ip_header, protocol_udp_header_t *udp_header, const uint32_t *payload, uint16_t payload_len, uint8_t udp_probe_variant, int port)
{
    const uint8_t *udp_payload = (const uint8_t *)payload;
    uint16_t udp_payload_len = payload_len;
    int16_t udp_packet_len;

    /* Rotate UDP probes across retries without port-specific hardcoding. */
    if (udp_probe_variant % PROTOCOL_UDP_TOTAL_PROBES == 1)
    {
        udp_payload = GET_PAYLOAD(port).payload_data;
        udp_payload_len = GET_PAYLOAD(port).len;
    }
    else if (udp_probe_variant % PROTOCOL_UDP_TOTAL_PROBES == 2)
    {
        udp_payload = NULL;
        udp_payload_len = 0;
    }

    udp_header->src_port = (uint16_t)(MIN_SRC_PORT + (rand() % (MAX_SRC_PORT - MIN_SRC_PORT)));
    udp_header->dst_port = port;
    udp_header->length = (uint16_t)(PROTOCOL_UDP_HEADER_SIZE + udp_payload_len);

    udp_packet_len = udp_packet_create(packet,
                                        packet_len,
                                        ip_header,
                                        udp_header,
                                        (const uint32_t *)udp_payload,
                                        udp_payload_len);
    return udp_packet_len;
}

static int16_t tcp_send_packet(uint8_t *packet, uint32_t packet_len, protocol_ip_header_t *ip_header, protocol_tcp_header_t *tcp_header, const uint32_t *payload, uint16_t payload_len, uint32_t cookie, int port)
{
    int16_t tcp_packet_len;

    tcp_header->src_port = (uint16_t)(MIN_SRC_PORT + (rand() % (MAX_SRC_PORT - MIN_SRC_PORT)));
    tcp_header->dst_port = port;
    tcp_header->seq_num = cookie;
    tcp_packet_len = tcp_packet_create(packet, packet_len, ip_header, tcp_header, payload, payload_len);

    return tcp_packet_len;
}

static void send_packet_init(uint8_t *packet, protocol_ip_header_t *ip_header, struct sockaddr_in *sin, uint32_t *cookie, const char *target_ip, int port, const char *local_ip, uint8_t scan_type)
{
    uint8_t scan_id = 0;

    memset(packet, 0, 128);
    ip_header->id = htons(rand() % PORT_MAX_PORT);
    ip_header->src = inet_addr(local_ip);
    ip_header->dst = inet_addr(target_ip);
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_addr.s_addr = inet_addr(target_ip);

    while ((scan_type & 1u) == 0u && scan_id < 7)
    {
        scan_type >>= 1;
        scan_id++;
    }
    *cookie = COOKIE_MAKE(scan_id, port);
}

// --- Sender Logic ---
void send_packet(int sockfd, const char *target_ip, int port, const char *local_ip, uint8_t scan_type, uint8_t udp_probe_variant)
{
    uint8_t packet[128];
    protocol_ip_header_t ip_header = {0};
    protocol_tcp_header_t tcp_header = {0};
    protocol_udp_header_t udp_header = {0};
    int16_t packet_len;
    struct sockaddr_in sin;
    uint32_t cookie;
    uint32_t payload = 0xb4050402; // Generic probe payload for UDP only

    send_packet_init(packet, &ip_header, &sin, &cookie, target_ip, port, local_ip, scan_type);

    if (set_scan_type_flag(&ip_header, &tcp_header, scan_type) < 0)
        return;

    if (ip_header.protocol == IPPROTO_UDP)
    {
        packet_len = udp_send_packet(packet,
                                            sizeof(packet),
                                            &ip_header,
                                            &udp_header,
                                            &payload,
                                            sizeof(payload),
                                            udp_probe_variant,
                                    port);
    }
    else
    {
        /* send header-only TCP probe (no application payload) */
        packet_len = tcp_send_packet(packet,
                                    sizeof(packet),
                                    &ip_header,
                                    &tcp_header,
                                    NULL,
                                    0,
                                    cookie,
                                    port);
    }
    
    if (packet_len < 0)
    {
        perror("Packet creation failed");
        return;
    }

    if (sendto(sockfd, packet, packet_len, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("sendto failed");
    }
}
