#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include <icmp.h>
#include <protocol_utils.h>
#include "response_states.h"
#include "scan_context.h"

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

int16_t icmp_header_parse(const uint8_t *buffer, uint8_t buffer_len, icmp_header_t *header)
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

int icmp_response_process(const uint8_t *transport, uint32_t ip_payload_len, const ip_header_t *ip_hdr)
{
    icmp_header_t icmp_hdr;
    int16_t icmp_len = icmp_header_parse(transport, (uint8_t)ip_payload_len, &icmp_hdr);
    if (icmp_len < 0)
        return 0;

    if (icmp_hdr.type == 3) // Destination Unreachable
    {
        ip_header_t inner_ip_hdr;
        // The ICMP payload embeds the original IP header + first 8 bytes
        // of the original transport header. The original destination port
        // (probe target) sits at byte offset 2 of that embedded header.
        const uint8_t *orig_ip = (const uint8_t *)(transport + ICMP_HEADER_LEN);
        int16_t orig_ip_hl;

        if (ip_payload_len < ICMP_HEADER_LEN + IP_MIN_HEADER_LEN + 4)
            return 0;

        orig_ip_hl = ip_header_parse(orig_ip,
                                        (uint8_t)(ip_payload_len - ICMP_HEADER_LEN),
                                        &inner_ip_hdr);
        if (orig_ip_hl < 0)
            return 0;

        if (ip_payload_len < (uint32_t)(ICMP_HEADER_LEN + orig_ip_hl + 4))
            return 0;

        uint16_t port = ntohs(*(const uint16_t *)(transport + ICMP_HEADER_LEN + orig_ip_hl + 2));
        if (port < PORT_START || port > PORT_END)
            return 0;

        results[port - 1].state = PORT_STATE_FILTERED;
        results[port - 1].response = RESPONSE_ICMP_UNREACHABLE;
        return 1;
    }
}