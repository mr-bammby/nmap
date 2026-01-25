#include "tcp.h"
#include "protcol_utils.h"

#define TCP_WINDOW_SIZE 65535
#define TCP_DATA_OFFSET 5  // 5 * 4 = 20 bytes (minimum header)
#define TCP_RESERVED_BITS 0
#define TCP_DEFAULT_ACK_NUM 0
#define TCP_DEFAULT_URGENT_PTR 0


int16_t tcp_header_create(uint8_t *buffer, uint8_t buffer_len, const tcp_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return TCP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < 20) {
        return TCP_ERR_BUFFER_TOO_SMALL; // Buffer too small for minimum TCP header
    }

    uint16_t *src_port_ptr = (uint16_t *)buffer;
    uint16_t *dst_port_ptr = (uint16_t *)(buffer + 2);
    uint32_t *seq_num_ptr = (uint32_t *)(buffer + 4);
    uint32_t *ack_num_ptr = (uint32_t *)(buffer + 8);
    uint8_t *data_offset_flags_ptr = buffer + 12;
    uint16_t *window_ptr = (uint16_t *)(buffer + 14);
    uint16_t *checksum_ptr = (uint16_t *)(buffer + 16);
    uint16_t *urgent_ptr = (uint16_t *)(buffer + 18);

    *src_port_ptr = htons(header->src_port);
    *dst_port_ptr = htons(header->dst_port);
    *seq_num_ptr = htonl(header->seq_num);
    *ack_num_ptr = htonl((header->flags & TCP_FLAG_ACK) ? TCP_DEFAULT_ACK_NUM : 0);
    *data_offset_flags_ptr = (TCP_DATA_OFFSET << 4) | header->flags;
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
    const uint8_t *data_offset_flags_ptr = buffer + 12;
    const uint16_t *checksum_ptr = (const uint16_t *)(buffer + 16);

    // Verify checksum before parsing
    uint16_t stored_checksum = ntohs(*checksum_ptr);
    
    // Temporarily zero checksum for verification
    uint8_t *buffer_copy = (uint8_t *)buffer;
    uint16_t *checksum_ptr_temp = (uint16_t *)(buffer_copy + 16);
    uint16_t original_checksum = *checksum_ptr_temp;
    *checksum_ptr_temp = 0;
    
    uint16_t calc_checksum = checksum(buffer, 20, 0);
    *checksum_ptr_temp = original_checksum;  // Restore original
    
    if (calc_checksum != stored_checksum) {
        return TCP_ERR_CHECKSUM;  // Checksum verification failed
    }

    header->src_port = ntohs(*src_port_ptr);
    header->dst_port = ntohs(*dst_port_ptr);
    header->seq_num = ntohl(*seq_num_ptr);
    header->flags = *data_offset_flags_ptr & 0x0F;

    return 20;
}
