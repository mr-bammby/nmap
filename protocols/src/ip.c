#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include <ip.h>
#include <protocol_utils.h>

int16_t ip_header_init(uint8_t *buffer, uint8_t buffer_len, const ip_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return IP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < IP_MIN_HEADER_LEN)
    {
        return IP_ERR_BUFFER_TOO_SMALL; // Buffer too small for minimum IP header
    }

    uint8_t *ip_hdr_version_length = (uint8_t *)buffer;
    uint8_t *ip_hdr_type_of_service = (uint8_t *)(buffer + 1);
    uint16_t *ip_hdr_total_length = (uint16_t *)(buffer + 2);
    uint16_t *ip_hdr_id = (uint16_t *)(buffer + 4);
    uint16_t *ip_hdr_offset = (uint16_t *)(buffer + 6);
    uint8_t *ip_hdr_time_to_live = (uint8_t *)(buffer + 8);
    uint8_t *ip_hdr_protocol = (uint8_t *)(buffer + 9);
    uint16_t *ip_hdr_checksum = (uint16_t *)(buffer + 10);
    uint32_t *ip_hdr_src = (uint32_t *)(buffer + 12);
    uint32_t *ip_hdr_dst = (uint32_t *)(buffer + 16);
    
    *ip_hdr_version_length = (VERSION_IPV4 << 4) | (IP_MIN_HEADER_LEN/4); // IPv4 and header length
    *ip_hdr_type_of_service = IP_DEFAULT_TOS; // Default TOS
    *ip_hdr_total_length = 0; // Temporarily zero, will be covered by encapsulate function
    *ip_hdr_id = htons(header->id); // Identification
    *ip_hdr_offset = htons(IP_DEFAULT_OFFSET); // Offset/fragmentation flags (Don't Fragment)
    *ip_hdr_time_to_live = IP_DEFAULT_TTL; // Default TTL
    *ip_hdr_protocol = header->protocol; // Protocol from IP header
    *ip_hdr_checksum = 0; // Temporarily zero, will be covered by encapsulate function
    *ip_hdr_src = htonl(header->src); // Source IP
    *ip_hdr_dst = htonl(header->dst); // Destination IP

    return IP_MIN_HEADER_LEN;
}

int16_t ip_header_encapsulate(uint8_t *buffer, uint16_t payload_length)
{

    if (buffer == NULL)
    {
        return IP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    uint16_t *ip_hdr_total_length = (uint16_t *)(buffer + 2);
    uint16_t *ip_hdr_checksum = (uint16_t *)(buffer + 10);
    
    uint16_t total_length = IP_MIN_HEADER_LEN + payload_length;
    *ip_hdr_total_length = htons(total_length);
    *ip_hdr_checksum = 0; // Reset checksum before calculation
    uint16_t calc_checksum = checksum(buffer, IP_MIN_HEADER_LEN, 0);
    *ip_hdr_checksum = htons(calc_checksum);

    return total_length;
}

int16_t ip_header_parse(const uint8_t *buffer, uint8_t buffer_len, ip_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return IP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < IP_MIN_HEADER_LEN) {
        return IP_ERR_BUFFER_TOO_SMALL;
    }

    uint16_t *ip_hdr_id = (uint16_t *)(buffer + 4);
    uint8_t *ip_hdr_protocol = (uint8_t *)(buffer + 9);
    uint16_t *ip_hdr_checksum = (uint16_t *)(buffer + 10);
    uint32_t *ip_hdr_src = (uint32_t *)(buffer + 12);
    uint32_t *ip_hdr_dst = (uint32_t *)(buffer + 16);

    // Verify checksum before parsing
    uint16_t original_checksum = ntohs(*ip_hdr_checksum);
    
    // Temporarily zero checksum for verification calculation
    // @ToDo: Optimize by avoiding full copy. Use negated checksum as an starting value of checksum calculation.
    uint8_t buffer_copy[IP_MIN_HEADER_LEN];
    memcpy(buffer_copy, buffer, IP_MIN_HEADER_LEN);
    uint16_t *checksum_ptr_temp = (uint16_t *)(buffer_copy + 10);
    *checksum_ptr_temp = 0;
    uint16_t calc_checksum = checksum(buffer_copy, IP_MIN_HEADER_LEN, 0);
    
    if (calc_checksum != original_checksum)
    {
        return IP_ERR_CHECKSUM;  // Checksum verification failed
    }

    header->id = ntohs(*ip_hdr_id);
    header->protocol = *ip_hdr_protocol;
    header->src = ntohl(*ip_hdr_src);
    header->dst = ntohl(*ip_hdr_dst);

    return IP_MIN_HEADER_LEN;
}