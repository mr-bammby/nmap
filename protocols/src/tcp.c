#include "tcp.h"
#include "protocol_utils.h"
#include <string.h>
#include <netinet/in.h>
#include "response_states.h"
#include "scan_context.h"

#define TCP_WINDOW_SIZE 65535
#define TCP_DATA_OFFSET 5  // 5 * 4 = 20 bytes (minimum header)
#define TCP_DEFAULT_ACK_NUM 0
#define TCP_DEFAULT_URGENT_PTR 0


int16_t tcp_header_create(uint8_t *buffer, uint8_t buffer_len, const tcp_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return TCP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < 20)
    {
        return TCP_ERR_BUFFER_TOO_SMALL; // Buffer too small for minimum TCP header
    }

    uint16_t *src_port_ptr = (uint16_t *)buffer;
    uint16_t *dst_port_ptr = (uint16_t *)(buffer + 2);
    uint32_t *seq_num_ptr = (uint32_t *)(buffer + 4);
    uint32_t *ack_num_ptr = (uint32_t *)(buffer + 8);
    uint8_t *data_offset_ptr = buffer + 12;
    uint8_t *flags_ptr = buffer + 13;
    uint16_t *window_ptr = (uint16_t *)(buffer + 14);
    uint16_t *checksum_ptr = (uint16_t *)(buffer + 16);
    uint16_t *urgent_ptr = (uint16_t *)(buffer + 18);

    *src_port_ptr = htons(header->src_port);
    *dst_port_ptr = htons(header->dst_port);
    *seq_num_ptr = htonl(header->seq_num);
    *ack_num_ptr = htonl((header->flags & TCP_FLAG_ACK) ? TCP_DEFAULT_ACK_NUM : 0);
    *data_offset_ptr = (TCP_DATA_OFFSET << 4);
    *flags_ptr = header->flags;
    *window_ptr = htons(TCP_WINDOW_SIZE);
    *checksum_ptr = 0;  // Temporarily zero for checksum calculation
    *urgent_ptr = htons((header->flags & TCP_FLAG_URG) ? TCP_DEFAULT_URGENT_PTR : 0);

    // Calculate and set checksum
    uint16_t calc_checksum = checksum(buffer, 20, 0);
    *checksum_ptr = htons(calc_checksum);

    return 20;
}

int16_t tcp_header_parse(const uint8_t *buffer, uint8_t buffer_len, tcp_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return TCP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < 20) {
        return TCP_ERR_BUFFER_TOO_SMALL;
    }

    const uint16_t *src_port_ptr = (const uint16_t *)buffer;
    const uint16_t *dst_port_ptr = (const uint16_t *)(buffer + 2);
    const uint32_t *seq_num_ptr = (const uint32_t *)(buffer + 4);
    const uint8_t *flags_ptr = buffer + 13;

    /*
     * Do not validate checksum here.
     * TCP checksum validation requires the IPv4 pseudo-header, which this
     * parser does not receive. Parse-only behavior is required for sniffed
     * on-wire packets in receiver logic.
     */

    header->src_port = ntohs(*src_port_ptr);
    header->dst_port = ntohs(*dst_port_ptr);
    header->seq_num = ntohl(*seq_num_ptr);
    header->flags = *flags_ptr;

    return 20;
}

//TODO - Implement other scan types (ACK, NULL, FIN, Xmas) and their response processing logic
int8_t tcp_response_process(const uint8_t *transport, uint32_t ip_payload_len, const ip_header_t *ip_hdr)
{
    tcp_header_t tcp_hdr;
    int16_t tcp_len = tcp_header_parse(transport, (uint8_t)ip_payload_len, &tcp_hdr);
    if (tcp_len < 0)
        return 0;

    if (tcp_hdr.src_port < PORT_START || tcp_hdr.src_port > PORT_END)
        return 0;

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
}
