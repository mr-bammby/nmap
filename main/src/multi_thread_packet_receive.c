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
#include "multi_thread_shared.h"

// --- Receiver Logic ---
int8_t multi_thread_process_packet(const unsigned char *packet, uint32_t packet_len, uint32_t link_header_len, scan_result_t **results, addr_hashmap_t *hash_map)
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
    th_flagging_array_access_t flag_arr;

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

    uint32_t hash_idx = 0;
    if (addr_hashmap_get(hash_map, ip_hdr.src, &hash_idx) != 0)
        return -1;

    LOGD("IP header parsed: src=%s dst=%s protocol=%d\n", src_str, dst_str, ip_hdr.protocol);

    switch (ip_hdr.protocol)
    {
        case IPPROTO_TCP:
            LOGD("Received TCP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
            return protocol_tcp_response_process(transport, ip_payload_len, &ip_hdr, results[hash_idx]);
        case IPPROTO_ICMP:
            LOGD("Received ICMP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
            th_flagging_array_init_access(&flag_arr, &(multi_thread_shared_flagging_array[hash_idx]), TH_LOCK_PRIORITY_HIGH);
            protocol_icmp_response_process(transport, ip_payload_len, &ip_hdr, results[hash_idx]);
            th_flagging_array_set(&flag_arr, results[hash_idx]->port, 1);
            return 0;
        case IPPROTO_UDP:
            LOGD("Received UDP packet from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
            th_flagging_array_init_access(&flag_arr, &(multi_thread_shared_flagging_array[hash_idx]), TH_LOCK_PRIORITY_HIGH);
            protocol_udp_response_process(transport, ip_payload_len, results[hash_idx]);
            th_flagging_array_set(&flag_arr, results[hash_idx]->port, 1);
            return 0;
        default:
            LOGD("No packet received from %s\n", inet_ntoa(*(struct in_addr *)&ip_hdr.src));
            return 0;
    }
}