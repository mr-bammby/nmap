#define MODULE_DEBUG DEBUG_PACKET_RECEIVE
#include "debug.h"
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "scan_defines.h"
#include "port_defines.h"
#include "scan_context.h"
#include "ip.h"
#include "tcp.h"
#include "icmp.h"
#include "udp.h"



// --- Receiver Logic ---
int8_t process_packet(const unsigned char *packet, uint32_t packet_len, uint32_t link_header_len, scan_result_t *results)
{
    //link_header_len is the number of bytes in the link-layer (L2) header of captured packets.
    //Captured packets start with L2 header (Ethernet/Linux cooked/etc), not IP directly.
    //The parser needs to skip those bytes before calling ip_header_parse().
    
    if (packet == NULL || packet_len < link_header_len + IP_MIN_HEADER_LEN)
        return 0;

    const uint8_t *ip_buf = (const uint8_t *)(packet + link_header_len);
    ip_header_t ip_hdr;
    int16_t ip_hl;
    const uint8_t *transport;
    uint32_t ip_payload_len;

    ip_hl = ip_header_parse(ip_buf, (uint8_t)(packet_len - link_header_len), &ip_hdr);
    if (ip_hl < 0)
        return 0;

    if (packet_len < (uint32_t)(link_header_len + ip_hl))
        return 0;

    transport = (const uint8_t *)(packet + link_header_len + ip_hl);
    ip_payload_len = packet_len - link_header_len - (uint32_t)ip_hl;

    LOGD("IP header parsed: src=%s dst=%s protocol=%d\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src), inet_ntoa(*(struct in_addr *)&ip_hdr.dst), ip_hdr.protocol);

    switch (ip_hdr.protocol)
    {
    case IPPROTO_TCP:
        LOGD("Received TCP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        return tcp_response_process(transport, ip_payload_len, &ip_hdr, results);
    case IPPROTO_ICMP:
        LOGD("Received ICMP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        return icmp_response_process(transport, ip_payload_len, &ip_hdr, results);
    
    case IPPROTO_UDP:
        LOGD("Received UDP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        return udp_response_process(transport, ip_payload_len, results);
    default:
        LOGD("No packet received from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        return 0;
    }
}