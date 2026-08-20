#define MODULE_DEBUG DEBUG_TCP
#include "debug.h"
#include "protocol_tcp.h"
#include "protocol_utils.h"
#include "protocol_ip.h"
#include <string.h>
#include <netinet/in.h>
#include "response_states.h"
#include "scan_context.h"
#include "scan_defines.h"
#include "argument_parser_port.h"


#define PROTOCOL_TCP_WINDOW_SIZE 65535
#define PROTOCOL_TCP_DATA_OFFSET 5  // 5 * 4 = 20 bytes (minimum header)
#define PROTOCOL_TCP_DEFAULT_ACK_NUM 0
#define PROTOCOL_TCP_DEFAULT_URGENT_PTR 0

typedef struct {
    uint32_t src_ip;
    uint32_t dst_ip;
    uint8_t reserved;
    uint8_t protocol;
    uint16_t tcp_length;
} tcp_pseudo_header_t;

int16_t protocol_tcp_checksum(const uint8_t *tcp_segment, uint16_t tcp_length_bytes, const protocol_ip_header_t *ip_header)
{
    tcp_pseudo_header_t pseudo_header;
    pseudo_header.src_ip = ip_header->src;
    pseudo_header.dst_ip = ip_header->dst;
    pseudo_header.reserved = 0;
    pseudo_header.protocol = ip_header->protocol;
    pseudo_header.tcp_length = htons(tcp_length_bytes);

    uint32_t sum_accum = protocol_utils_checksum_accumulate(&pseudo_header, sizeof(pseudo_header), 0);
    uint16_t sum_final = protocol_utils_checksum_final(tcp_segment, tcp_length_bytes, sum_accum);

    return sum_final;
}

int16_t protocol_tcp_header_create(uint8_t *buffer, uint8_t buffer_len, const protocol_tcp_header_t *tcp_header, const protocol_ip_header_t *ip_header, const uint32_t *payload, uint16_t payload_len)
{
    if (buffer == NULL || tcp_header == NULL || ip_header == NULL)
    {
        return PROTOCOL_TCP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < (20 + payload_len * 4)) // Minimum TCP header + payload
    {
        return PROTOCOL_TCP_ERR_BUFFER_TOO_SMALL; // Buffer too small for minimum TCP header
    }

    uint16_t *src_port_ptr = (uint16_t *)buffer;
    uint16_t *dst_port_ptr = (uint16_t *)(buffer + 2);
    uint32_t *seq_num_ptr = (uint32_t *)(buffer + 4);
    uint32_t *ack_num_ptr = (uint32_t *)(buffer + 8);
    uint16_t *data_offset_flags_ptr = (uint16_t *)(buffer + 12);
    uint16_t *window_ptr = (uint16_t *)(buffer + 14);
    uint16_t *checksum_ptr = (uint16_t *)(buffer + 16);
    uint16_t *urgent_ptr = (uint16_t *)(buffer + 18);

    *src_port_ptr = htons(tcp_header->src_port);
    *dst_port_ptr = htons(tcp_header->dst_port);
    *seq_num_ptr = htonl(tcp_header->seq_num);
    /* For ACK probes, reuse seq_num as ACK cookie so RST replies can be correlated. */
    *ack_num_ptr = htonl((tcp_header->flags & PROTOCOL_TCP_FLAG_ACK) ? tcp_header->seq_num : PROTOCOL_TCP_DEFAULT_ACK_NUM);
    *data_offset_flags_ptr = htons(((PROTOCOL_TCP_DATA_OFFSET + payload_len) << 12) | (tcp_header->flags & 0x00FF));
    *window_ptr = htons(PROTOCOL_TCP_WINDOW_SIZE);
    *checksum_ptr = 0;  // Temporarily zero for checksum calculation
    *urgent_ptr = htons((tcp_header->flags & PROTOCOL_TCP_FLAG_URG) ? PROTOCOL_TCP_DEFAULT_URGENT_PTR : 0);

    if (payload && payload_len > 0)
    {
        memcpy(buffer + 20, payload, payload_len * 4); // Copy payload after TCP header
    }

    uint16_t tcp_length_bytes = 20 + payload_len * 4;
    uint16_t calc_checksum = protocol_tcp_checksum(buffer, tcp_length_bytes, ip_header);
    *checksum_ptr = htons(calc_checksum);

    return tcp_length_bytes; // Total length of TCP header + payload
}

int16_t protocol_tcp_header_parse(const uint8_t *buffer, uint8_t buffer_len, protocol_tcp_header_t *tcp_header, const protocol_ip_header_t *ip_header)
{
    if (buffer == NULL || tcp_header == NULL || ip_header == NULL)
    {
        return PROTOCOL_TCP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < PROTOCOL_TCP_HEADER_SIZE)
    {
        return PROTOCOL_TCP_ERR_BUFFER_TOO_SMALL;
    }

    uint16_t *src_port_ptr = (uint16_t *)buffer;
    uint16_t *dst_port_ptr = (uint16_t *)(buffer + 2);
    uint32_t *seq_num_ptr = (uint32_t *)(buffer + 4);
    uint32_t *ack_num_ptr = (uint32_t *)(buffer + 8);
    uint16_t *data_offset_flags_ptr = (uint16_t *)(buffer + 12);
    uint16_t *window_ptr = (uint16_t *)(buffer + 14);
    uint16_t *checksum_ptr = (uint16_t *)(buffer + 16);
    uint16_t *urgent_ptr = (uint16_t *)(buffer + 18);

    /*
     * Verify the TCP checksum using the RFC-style pseudo-header plus the
     * TCP segment, matching the generation logic used for outbound probes.
     * The checksum field is zeroed temporarily during the calculation and
     * then compared against the field carried in the packet.
     */
    uint16_t stored_checksum = ntohs(*checksum_ptr);
    uint8_t buffer_copy[256] = {0};

    memcpy(buffer_copy, buffer, buffer_len);
    uint16_t *checksum_ptr_temp = (uint16_t *)(buffer_copy + 16);
    *checksum_ptr_temp = 0;

    uint16_t calc_checksum = protocol_tcp_checksum(buffer_copy, (uint16_t)buffer_len, ip_header);
    if (calc_checksum != stored_checksum)
    {
        LOGD("TCP checksum mismatch: calculated 0x%04x, expected 0x%04x\n",
             calc_checksum, stored_checksum);
    }

    tcp_header->src_port = ntohs(*src_port_ptr);
    tcp_header->dst_port = ntohs(*dst_port_ptr);
    tcp_header->seq_num = ntohl(*seq_num_ptr);
    tcp_header->flags = ntohs(*data_offset_flags_ptr) & 0x0FF;

    return 20;
}

int8_t protocol_tcp_response_process(const uint8_t *transport, uint32_t ip_payload_len, const protocol_ip_header_t *ip_hdr, scan_result_t *results, const argparse_port_set_t *ports)
{
    protocol_tcp_header_t tcp_hdr;
    uint32_t cookie = 0;
    uint32_t ack_num;

    int16_t tcp_len = protocol_tcp_header_parse(transport, (uint8_t)ip_payload_len, &tcp_hdr, ip_hdr);
    if (tcp_len < 0)
    {
        LOGE("Failed to parse TCP header: %d\n", tcp_len);
        return 0;
    }


    ack_num = ntohl(*(const uint32_t *)(transport + 8));
    if (tcp_hdr.flags & PROTOCOL_TCP_FLAG_RST)
    {
        cookie = tcp_hdr.seq_num;        // ACK scan RST reply
    }
    else if (tcp_hdr.flags & PROTOCOL_TCP_FLAG_ACK)
    {
        cookie = ack_num - 1;   // SYN / NULL / FIN / XMAS replies
    }
    else if (tcp_hdr.flags == 0)
    {
        cookie = ack_num - 1;
    }

    if (!COOKIE_VALID(cookie))
        return 0;

    uint8_t scan_id = COOKIE_SCAN(cookie);
    uint8_t scan_flag = (uint8_t)(1u << scan_id);
    uint16_t port   = COOKIE_PORT(cookie);
    LOGD("ScanID %d, ScanFlag %d and Port %d\n", scan_id, scan_flag, port);
    int port_index = 0;
    if (argparse_port_find(ports, port, &port_index) != 0)
    {
        return 0;
    }

    switch (scan_flag)
    {
    case SCAN_FLG_SYN:
        if ((tcp_hdr.flags & PROTOCOL_TCP_FLAG_SYN) && (tcp_hdr.flags & PROTOCOL_TCP_FLAG_ACK))
        {
            results[port_index].response_syn = RESPONSE_SYN_ACK;
            return 1;
        }
        else if (tcp_hdr.flags & PROTOCOL_TCP_FLAG_RST)
        {
            results[port_index].response_syn = RESPONSE_RST;
            return 1;
        }
        else
        {
            LOGE("Received TCP packet with unexpected flags 0x%02x from %s:%d\n", tcp_hdr.flags, inet_ntoa(*(struct in_addr *)&ip_hdr->src), tcp_hdr.src_port);
            return 0;
        }
        break;
    case SCAN_FLG_ACK:
        if (tcp_hdr.flags & PROTOCOL_TCP_FLAG_RST)        {
            results[port_index].response_ack = RESPONSE_RST;
            return 1;
        }
        else        {
            LOGE("Received TCP packet with unexpected flags 0x%02x from %s:%d\n", tcp_hdr.flags, inet_ntoa(*(struct in_addr *)&ip_hdr->src), tcp_hdr.src_port);
            return 0;
        }
        break;
    case SCAN_FLG_NULL:
        if (tcp_hdr.flags == 0)        {
            results[port_index].response_null = RESPONSE_SYN_ACK; // Reuse RESPONSE_SYN_ACK to indicate open for NULL scan
            return 1;
        }
        else        {
            LOGE("Received TCP packet with unexpected flags 0x%02x from %s:%d\n", tcp_hdr.flags, inet_ntoa(*(struct in_addr *)&ip_hdr->src), tcp_hdr.src_port);
            return 0;
        }
        break;
    case SCAN_FLG_FIN:
        if (tcp_hdr.flags & PROTOCOL_TCP_FLAG_RST)        {
            results[port_index].response_fin = RESPONSE_RST;
            return 1;
        }
        else        {
            LOGE("Received TCP packet with unexpected flags 0x%02x from %s:%d\n", tcp_hdr.flags, inet_ntoa(*(struct in_addr *)&ip_hdr->src), tcp_hdr.src_port);
            return 0;
        }
        break;
    case SCAN_FLG_XMAS:
        if (tcp_hdr.flags & PROTOCOL_TCP_FLAG_RST)        {
            results[port_index].response_xmas = RESPONSE_RST;
            return 1;
        }
        else        {
            LOGE("Received TCP packet with unexpected flags 0x%02x from %s:%d\n", tcp_hdr.flags, inet_ntoa(*(struct in_addr *)&ip_hdr->src), tcp_hdr.src_port);
            return 0;
        }
        break;
    default:
        LOGE("Received TCP packet with unknown scan ID %d from %s:%d\n", scan_id, inet_ntoa(*(struct in_addr *)&ip_hdr->src), tcp_hdr.src_port);
        return 0;
    }
}
