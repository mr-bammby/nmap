#define MODULE_DEBUG DEBUG_UDP
#include "debug.h"
#include "protocol_udp.h"
#include "protocol_ip.h"
#include "protocol_utils.h"
#include <string.h>
#include <netinet/in.h>
#include "response_states.h"
#include "scan_context.h"
#include "argument_parser_port.h"


int16_t protocol_udp_header_create(uint8_t *buffer, uint8_t buffer_len, const protocol_udp_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return PROTOCOL_UDP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < PROTOCOL_UDP_HEADER_SIZE)
    {
        return PROTOCOL_UDP_ERR_BUFFER_TOO_SMALL; // Buffer too small for UDP header
    }

    uint16_t *src_port_ptr = (uint16_t *)buffer;
    uint16_t *dst_port_ptr = (uint16_t *)(buffer + 2);
    uint16_t *length_ptr = (uint16_t *)(buffer + 4);
    uint16_t *checksum_ptr = (uint16_t *)(buffer + 6);

    *src_port_ptr = htons(header->src_port);
    *dst_port_ptr = htons(header->dst_port);
    *length_ptr = htons(header->length);
    /* IPv4 UDP checksum of 0 means "not used" and avoids invalid pseudo-header checksum here. */
    *checksum_ptr = 0;

    return PROTOCOL_UDP_HEADER_SIZE;
}

int16_t protocol_udp_header_parse(const uint8_t *buffer, uint8_t buffer_len, protocol_udp_header_t *header)
{
    if (buffer == NULL || header == NULL)
    {
        return PROTOCOL_UDP_ERR_INVALID_ARGUMENT; // Invalid argument
    }

    if (buffer_len < PROTOCOL_UDP_HEADER_SIZE) {
        return PROTOCOL_UDP_ERR_BUFFER_TOO_SMALL;
    }

    const uint16_t *src_port_ptr = (const uint16_t *)buffer;
    const uint16_t *dst_port_ptr = (const uint16_t *)(buffer + 2);
    const uint16_t *length_ptr = (const uint16_t *)(buffer + 4);
    const uint16_t *checksum_ptr = (const uint16_t *)(buffer + 6);

    header->src_port = ntohs(*src_port_ptr);
    header->dst_port = ntohs(*dst_port_ptr);
    header->length = ntohs(*length_ptr);


    // Temporarily zero checksum for verification calculation
    // @ToDo: Optimize by avoiding full copy. Use negated checksum as an starting value of checksum calculation.
    uint8_t buffer_copy[PROTOCOL_UDP_HEADER_SIZE];
    memcpy(buffer_copy, buffer, PROTOCOL_UDP_HEADER_SIZE);

    uint16_t *checksum_ptr_temp = (uint16_t *)(buffer_copy + 6);
    uint16_t original_checksum = ntohs(*checksum_ptr_temp);
    uint16_t calc_checksum;

    *checksum_ptr_temp = 0;  // Temporarily zero checksum for verification
    calc_checksum = protocol_utils_checksum_final(buffer_copy, PROTOCOL_UDP_HEADER_SIZE, 0);

    if (original_checksum != 0 && calc_checksum != 0 && calc_checksum != original_checksum)
    {
        return PROTOCOL_UDP_ERR_CHECKSUM; // Checksum mismatch
    }

    return PROTOCOL_UDP_HEADER_SIZE;
}

int8_t protocol_udp_response_process(const uint8_t *transport, uint32_t ip_payload_len, scan_result_t *results, const argparse_port_set_t *ports, uint16_t *ret_port_id)
{
    if (transport == NULL || ip_payload_len < PROTOCOL_UDP_HEADER_SIZE || results == NULL || ports == NULL)
        return 0;

    // For UDP, a reply to the probe indicates the port is open.
    // The destination port in the reply corresponds to the port we probed.
    uint16_t port = ntohs(*(const uint16_t *)(transport)); // Destination port
    if (port < PORT_START || port > PORT_END)
        return 0;

    int port_index = 0;
    if (argparse_port_find(ports, port, &port_index) != 0)
        return 0;

    results[port_index].response_udp = RESPONSE_UDP_REPLY;
    if (ret_port_id != NULL)
        *ret_port_id = port_index;
    return 1;
}
