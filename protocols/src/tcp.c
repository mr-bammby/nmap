#include "tcp.h"
#include "protocol_utils.h"
#include "ip.h"
#include <string.h>
#include <netinet/in.h>
#include "response_states.h"
#include "scan_context.h"

#define TCP_WINDOW_SIZE 65535
#define TCP_DATA_OFFSET 5  // 5 * 4 = 20 bytes (minimum header)
#define TCP_DEFAULT_ACK_NUM 0
#define TCP_DEFAULT_URGENT_PTR 0

typedef struct {
    uint32_t src_ip;
    uint32_t dst_ip;
    uint8_t reserved;
    uint8_t protocol;
    uint16_t tcp_length;
} tcp_pseudo_header_t;

int16_t tcp_checksum(const uint8_t *tcp_segment, uint16_t tcp_length, const ip_header_t *ip_header)
{
    tcp_pseudo_header_t pseudo_header;
    pseudo_header.src_ip = ip_header->src;
    pseudo_header.dst_ip = ip_header->dst;
    pseudo_header.reserved = 0;
    pseudo_header.protocol = ip_header->protocol;
    pseudo_header.tcp_length = htons(tcp_length * 4); // TCP length in bytes

    printf("Calculating TCP checksum with pseudo-header: src_ip=%s, dst_ip=%s, protocol=%d, tcp_length=%d\n",
           inet_ntoa(*(struct in_addr *)&pseudo_header.src_ip),
           inet_ntoa(*(struct in_addr *)&pseudo_header.dst_ip),
           pseudo_header.protocol,
           tcp_length * 4);

    // Calculate checksum over pseudo-header and TCP segment
    uint32_t sum_accum = 0;
    uint16_t sum_final;
    sum_accum = checksum_accumulate(&pseudo_header, sizeof(pseudo_header), 0);
    printf("Pseudo-header checksum accumulation: 0x%08x\n", sum_accum);
    sum_final = checksum_final(tcp_segment, tcp_length * 4, sum_accum);
    
    return sum_final;
}

int16_t tcp_header_create(uint8_t *buffer, uint8_t buffer_len, const tcp_header_t *tcp_header, const ip_header_t *ip_header, const uint32_t *payload, uint16_t payload_len)
{
    if (buffer == NULL || tcp_header == NULL || ip_header == NULL)
    {
        return TCP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < (20 + payload_len * 4)) // Minimum TCP header + payload
    {
        return TCP_ERR_BUFFER_TOO_SMALL; // Buffer too small for minimum TCP header
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
    *ack_num_ptr = htonl((tcp_header->flags & TCP_FLAG_ACK) ? TCP_DEFAULT_ACK_NUM : 0);
    *data_offset_flags_ptr = htons(((TCP_DATA_OFFSET + payload_len) << 12) | (tcp_header->flags & 0x00FF));
    *window_ptr = htons(TCP_WINDOW_SIZE);
    *checksum_ptr = 0;  // Temporarily zero for checksum calculation
    *urgent_ptr = htons((tcp_header->flags & TCP_FLAG_URG) ? TCP_DEFAULT_URGENT_PTR : 0);

    if (payload && payload_len > 0)
    {
        memcpy(buffer + 20, payload, payload_len * 4); // Copy payload after TCP header
    }

    uint16_t calc_checksum = tcp_checksum(buffer, 5 + payload_len, ip_header);
    *checksum_ptr = calc_checksum;

    return 20 + payload_len * 4; // Total length of TCP header + payload
}

int16_t tcp_header_parse(const uint8_t *buffer, uint8_t buffer_len, tcp_header_t *tcp_header, const ip_header_t *ip_header)
{
    if (buffer == NULL || tcp_header == NULL || ip_header == NULL)
    {
        return TCP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < 20) {
        return TCP_ERR_BUFFER_TOO_SMALL;
    }
    print_bytes(buffer, buffer_len);

    uint16_t *src_port_ptr = (uint16_t *)buffer;
    uint16_t *dst_port_ptr = (uint16_t *)(buffer + 2);
    uint32_t *seq_num_ptr = (uint32_t *)(buffer + 4);
    uint32_t *ack_num_ptr = (uint32_t *)(buffer + 8);
    uint16_t *data_offset_flags_ptr = (uint16_t *)(buffer + 12);
    uint16_t *window_ptr = (uint16_t *)(buffer + 14);
    uint16_t *checksum_ptr = (uint16_t *)(buffer + 16);
    uint16_t *urgent_ptr = (uint16_t *)(buffer + 18);

    // Verify checksum before parsing
    uint16_t stored_checksum = ntohs(*checksum_ptr);
    
    // Temporarily zero checksum for verification calculation
    // @ToDo: Optimize by avoiding full copy. Use negated checksum as an starting value of checksum calculation.
    uint8_t buffer_copy[20] = {0};
    
    memcpy(buffer_copy, buffer, 20);
    uint16_t *checksum_ptr_temp = (uint16_t *)(buffer_copy + 16);
    uint16_t original_checksum __attribute__((unused)) = *checksum_ptr_temp;
    uint16_t calc_checksum;
    *checksum_ptr_temp = 0;
    
    calc_checksum = tcp_checksum(buffer_copy, buffer_len, ip_header);
    
    if (calc_checksum != stored_checksum)
    {
        printf("TCP checksum verification failed: calculated 0x%04x, expected 0x%04x\n", calc_checksum, stored_checksum);
    }

    tcp_header->src_port = ntohs(*src_port_ptr);
    tcp_header->dst_port = ntohs(*dst_port_ptr);
    tcp_header->seq_num = ntohl(*seq_num_ptr);
    tcp_header->flags = ntohs(*data_offset_flags_ptr) & 0x0FF;

    return 20;
}

//TODO - Implement other scan types (ACK, NULL, FIN, Xmas) and their response processing logic
int8_t tcp_response_process(const uint8_t *transport, uint32_t ip_payload_len, const ip_header_t *ip_hdr)
{
    tcp_header_t tcp_hdr;
    int16_t tcp_len = tcp_header_parse(transport, (uint8_t)ip_payload_len, &tcp_hdr, ip_hdr);
    if (tcp_len < 0)
    {
        printf("Failed to parse TCP header: %d\n", tcp_len);
        return 0;
    }

    if (tcp_hdr.src_port < PORT_START || tcp_hdr.src_port > PORT_END)
    {
        printf("Received TCP packet with source port %d outside of expected range\n", tcp_hdr.src_port);
        return 0;
    }

    if ((tcp_hdr.flags & TCP_FLAG_SYN) && (tcp_hdr.flags & TCP_FLAG_ACK))
    {
        results[tcp_hdr.src_port - 1].response_syn = RESPONSE_SYN_ACK;
        return 1;
    }
    else if (tcp_hdr.flags & TCP_FLAG_RST)
    {
        results[tcp_hdr.src_port - 1].response_syn = RESPONSE_RST;
        return 1;
    }
    else
    {
        printf("Received TCP packet with unexpected flags 0x%02x from %s:%d\n", tcp_hdr.flags, inet_ntoa(*(struct in_addr *)&ip_hdr->src), tcp_hdr.src_port);
        return 0;
    }
}
