#ifndef ICMP_H
#define ICMP_H

#include <inttypes.h>
#include "protocol_ip.h"
#include "response_states.h"
#include "argument_parser_types.h"

#define PROTOCOL_ICMP_HEADER_LEN 8
#define PROTOCOL_ICMP_TYPE_ECHO_REQUEST 8
#define PROTOCOL_ICMP_TYPE_ECHO_REPLY 0
#define PROTOCOL_ICMP_ERR_BUFFER_TOO_SMALL -1
#define PROTOCOL_ICMP_ERR_INVALID_ARGUMENT -2

typedef struct icmp_header {
    uint8_t  type;               /* ICMP type */
    uint8_t  code;               /* ICMP code */
    uint16_t identifier;         /* Identifier */
    uint16_t sequence_number;    /* Sequence number */
} protocol_icmp_header_t;
/**
 * Initialize an ICMP header in the provided buffer.
 *
 * @param buffer Pointer to the buffer where the ICMP header will be initialized.
 * @param buffer_len Length of the buffer in bytes.
 * @param header Pointer to the protocol_icmp_header_t structure containing header fields.
 * @return Number of bytes written to the buffer, or a negative error code.
 */
int16_t protocol_icmp_header_init(uint8_t *buffer, uint8_t buffer_len, const protocol_icmp_header_t *header);

/**
 * Finalize ICMP header by setting checksum over header + payload.
 *
 * @param buffer Pointer to the ICMP header buffer.
 * @param payload_length Length of payload in bytes.
 * @return Total ICMP length (header + payload), or a negative error code.
 */
int16_t protocol_icmp_header_encapsulate(uint8_t *buffer, uint16_t payload_length);

/**
 * Parse an ICMP header from a buffer.
 *
 * @param buffer Pointer to buffer containing the ICMP header.
 * @param buffer_len Length of the buffer in bytes.
 * @param header Output structure for parsed fields.
 * @return Number of bytes read, or a negative error code.
 */
int16_t protocol_icmp_header_parse(const uint8_t *buffer, uint8_t buffer_len, protocol_icmp_header_t *header);

int protocol_icmp_response_process(const uint8_t *transport, uint32_t ip_payload_len, const protocol_ip_header_t *ip_hdr, scan_result_t *results, const argparse_port_set_t *ports);

#endif // ICMP_H