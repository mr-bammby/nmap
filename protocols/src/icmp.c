#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include <icmp.h>
#include <protocol_utils.h>

int16_t icmp_header_init(uint8_t *buffer, uint8_t buffer_len, const icmp_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return ICMP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < ICMP_HEADER_LEN)
    {
        return ICMP_ERR_BUFFER_TOO_SMALL; // Buffer too small for ICMP header
    }

    uint8_t *icmp_type = (uint8_t *)buffer;
    uint8_t *icmp_code = (uint8_t *)(buffer + 1);
    uint16_t *icmp_checksum = (uint16_t *)(buffer + 2);
    uint16_t *icmp_identifier = (uint16_t *)(buffer + 4);
    uint16_t *icmp_sequence_number = (uint16_t *)(buffer + 6);

    *icmp_type = header->type; // ICMP type
    *icmp_code = header->code; // ICMP code
    *icmp_checksum = 0; // Temporarily zero, will be calculated in encapsulate function
    *icmp_identifier = htons(header->identifier); // Identifier
    *icmp_sequence_number = htons(header->sequence_number); // Sequence number

    return ICMP_HEADER_LEN;
}

int16_t icmp_header_encapsulate(uint8_t *buffer, uint16_t payload_length)
{
    if (buffer == NULL)
    {
        return ICMP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    uint16_t *icmp_checksum = (uint16_t *)(buffer + 2);
    
    *icmp_checksum = 0; // Reset checksum before calculation
    uint16_t total_length = ICMP_HEADER_LEN + payload_length;
    uint16_t calc_checksum = checksum(buffer, total_length, 0);
    *icmp_checksum = htons(calc_checksum);

    return total_length;
}

uint16_t icmp_header_parse(const uint8_t *buffer, uint8_t buffer_len, icmp_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return ICMP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < ICMP_HEADER_LEN)
    {
        return ICMP_ERR_BUFFER_TOO_SMALL; // Buffer too small for ICMP header
    }

    const uint8_t *icmp_type = (const uint8_t *)buffer;
    const uint8_t *icmp_code = (const uint8_t *)(buffer + 1);
    const uint16_t *icmp_identifier = (const uint16_t *)(buffer + 4);
    const uint16_t *icmp_sequence_number = (const uint16_t *)(buffer + 6);

    header->type = *icmp_type; // ICMP type
    header->code = *icmp_code; // ICMP code
    header->identifier = ntohs(*icmp_identifier); // Identifier
    header->sequence_number = ntohs(*icmp_sequence_number); // Sequence number

    return ICMP_HEADER_LEN;
}