#include "udp.h"
#include "protocol_utils.h"
#include <string.h>
#include <netinet/in.h>

#define UDP_HEADER_SIZE 8

int16_t udp_header_create(uint8_t *buffer, uint8_t buffer_len, const udp_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return UDP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < UDP_HEADER_SIZE)
    {
        return UDP_ERR_BUFFER_TOO_SMALL; // Buffer too small for UDP header
    }

    uint16_t *src_port_ptr = (uint16_t *)buffer;
    uint16_t *dst_port_ptr = (uint16_t *)(buffer + 2);
    uint16_t *length_ptr = (uint16_t *)(buffer + 4);
    uint16_t *checksum_ptr = (uint16_t *)(buffer + 6);

    *src_port_ptr = htons(header->src_port);
    *dst_port_ptr = htons(header->dst_port);
    *length_ptr = htons(header->length);
    *checksum_ptr = 0;  // Temporarily zero for checksum calculation

    // Calculate and set checksum
    uint16_t calc_checksum = checksum(buffer, 8, 0);
    *checksum_ptr = htons(calc_checksum);

    return UDP_HEADER_SIZE;
}

int16_t udp_header_parse(const uint8_t *buffer, uint8_t buffer_len, udp_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return UDP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < UDP_HEADER_SIZE) {
        return UDP_ERR_BUFFER_TOO_SMALL;
    }

    const uint16_t *src_port_ptr = (const uint16_t *)buffer;
    const uint16_t *dst_port_ptr = (const uint16_t *)(buffer + 2);
    const uint16_t *length_ptr = (const uint16_t *)(buffer + 4);
    const uint16_t *checksum_ptr = (const uint16_t *)(buffer + 6);

    header->src_port = ntohs(*src_port_ptr);
    header->dst_port = ntohs(*dst_port_ptr);
    header->length = ntohs(*length_ptr);
    header->checksum = ntohs(*checksum_ptr);

    // Temporarily zero checksum for verification calculation
    // @ToDo: Optimize by avoiding full copy. Use negated checksum as an starting value of checksum calculation.
    uint8_t buffer_copy[UDP_HEADER_SIZE];
    uint16_t *checksum_ptr_temp = (uint16_t *)(buffer_copy + 6);
    uint16_t original_checksum = *checksum_ptr_temp;
    uint16_t calc_checksum;
    *checksum_ptr_temp = 0;

    memcpy(buffer_copy, buffer, UDP_HEADER_SIZE);
    calc_checksum = checksum(buffer_copy, UDP_HEADER_SIZE, 0);

    if (calc_checksum != 0 && calc_checksum != original_checksum)
    {
        return UDP_ERR_CHECKSUM; // Checksum mismatch
    }

    return UDP_HEADER_SIZE;
}