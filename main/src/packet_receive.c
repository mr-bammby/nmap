#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "nmap_types.h"
#include "scan_context.h"
#include "ip.h"
#include "tcp.h"
#include "icmp.h"
#include "udp.h"
#include "debug.h"

#if DEBUG
#warning DEBUG IS ENABLED IN PACKET_RECEIVE
#endif


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
    #if DEBUG_PACKET_RECEIVE
    printf("IP header parsed: src=%s dst=%s protocol=%d\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src), inet_ntoa(*(struct in_addr *)&ip_hdr.dst), ip_hdr.protocol);
    #endif /* DEBUG_PACKET_RECEIVE */
    switch (ip_hdr.protocol)
    {
    case IPPROTO_TCP:
        #if DEBUG_PACKET_RECEIVE
        printf("Received TCP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        #endif /* DEBUG_PACKET_RECEIVE */
        return tcp_response_process(transport, ip_payload_len, &ip_hdr, results);
    case IPPROTO_ICMP:
        #if DEBUG_PACKET_RECEIVE
        printf("Received ICMP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        #endif /* DEBUG_PACKET_RECEIVE */
        return icmp_response_process(transport, ip_payload_len, &ip_hdr, results);
    
    case IPPROTO_UDP:
        #if DEBUG_PACKET_RECEIVE
        printf("Received UDP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        #endif /* DEBUG_PACKET_RECEIVE */
        return udp_response_process(transport, ip_payload_len, results);
    default:
        #if DEBUG_PACKET_RECEIVE
        printf("No packet received from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        #endif /* DEBUG_PACKET_RECEIVE */
        return 0;
    }
}