#define MODULE_DEBUG DEBUG_MULTI_THREAD_PACKET_RECEIVE
#include "debug.h"
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "scan_defines.h"
#include "port_defines.h"
#include "scan_context.h"
#include "protocol_ip.h"
#include "protocol_tcp.h"
#include "protocol_icmp.h"
#include "protocol_udp.h"



// --- Receiver Logic ---
int8_t multi_thread_process_packet(const unsigned char *packet, uint32_t packet_len, uint32_t link_header_len, scan_result_t **results)
{
    //link_header_len is the number of bytes in the link-layer (L2) header of captured packets.
    //Captured packets start with L2 header (Ethernet/Linux cooked/etc), not IP directly.
    //The parser needs to skip those bytes before calling ip_header_parse().
    
    if (packet == NULL || packet_len < link_header_len + PROTOCOL_IP_MIN_HEADER_LEN)
        return 0;

    const uint8_t *ip_buf = (const uint8_t *)(packet + link_header_len);
    protocol_ip_header_t ip_hdr;
    int16_t ip_hl;
    const uint8_t *transport;
    uint32_t ip_payload_len;

    ip_hl = protocol_ip_header_parse(ip_buf, (uint8_t)(packet_len - link_header_len), &ip_hdr);
    if (ip_hl < 0)
        return 0;

    if (packet_len < (uint32_t)(link_header_len + ip_hl))
        return 0;

    transport = (const uint8_t *)(packet + link_header_len + ip_hl);
    ip_payload_len = packet_len - link_header_len - (uint32_t)ip_hl;

    char src_str[INET_ADDRSTRLEN];
    char dst_str[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &ip_hdr.src, src_str, sizeof(src_str));
    inet_ntop(AF_INET, &ip_hdr.dst, dst_str, sizeof(dst_str));

    LOGD("IP header parsed: src=%s dst=%s protocol=%d\n", src_str, dst_str, ip_hdr.protocol);
    switch (ip_hdr.protocol)
    {
    case IPPROTO_TCP:
        LOGD("Received TCP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        if (strncmp(src_str, "45.33.32.156", strlen("45.33.32.156")) == 0)
        {
            protocol_tcp_response_process(transport, ip_payload_len, &ip_hdr, results[0]);
            LOGD("Port SYN 45.33.32.156 %d\n", results[0][52].port);
            LOGD("Response SYN 45.33.32.156 %d\n", results[0][52].response_syn);
        }
        if (strncmp(src_str, "8.8.8.8", strlen("8.8.8.8")) == 0)
        {
            protocol_tcp_response_process(transport, ip_payload_len, &ip_hdr, results[1]);
            LOGD("Port SYN 8.8.8.8 %d\n", results[1][79].response_syn);
            LOGD("Response SYN 8.8.8.8 %d\n", results[1][79].response_syn);
        }
        return 0;
    case IPPROTO_ICMP:
        LOGD("Received ICMP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        //return protocol_icmp_response_process(transport, ip_payload_len, &ip_hdr, results);
        return 0;
    
    case IPPROTO_UDP:
        LOGD("Received UDP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        return 0;
        //return protocol_udp_response_process(transport, ip_payload_len, results);
    default:
        LOGD("No packet received from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
        return 0;
    }
}