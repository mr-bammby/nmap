#ifndef ICMP_H
#define ICMP_H

#include <inttypes.h>
#include "ip.h"

#define ICMP_HEADER_LEN 8
#define ICMP_TYPE_ECHO_REQUEST 8
#define ICMP_TYPE_ECHO_REPLY 0
#define ICMP_ERR_BUFFER_TOO_SMALL -1
#define ICMP_ERR_INVALID_ARGUMENT -2

typedef struct icmp_header {
    uint8_t  type;               /* ICMP type */
    uint8_t  code;               /* ICMP code */
    uint16_t identifier;         /* Identifier */
    uint16_t sequence_number;    /* Sequence number */
} icmp_header_t;
/**
 * Initialize an ICMP header in the provided buffer.
 *
 * @param buffer Pointer to the buffer where the ICMP header will be initialized.
 * @param buffer_len Length of the buffer in bytes.
 * @param header Pointer to the icmp_header_t structure containing header fields.
 * @return Number of bytes written to the buffer, or a negative error code.
 */
int16_t icmp_header_init(uint8_t *buffer, uint8_t buffer_len, const icmp_header_t *header);

/**
 * Finalize ICMP header by setting checksum over header + payload.
 *
 * @param buffer Pointer to the ICMP header buffer.
 * @param payload_length Length of payload in bytes.
 * @return Total ICMP length (header + payload), or a negative error code.
 */
int16_t icmp_header_encapsulate(uint8_t *buffer, uint16_t payload_length);

/**
 * Parse an ICMP header from a buffer.
 *
 * @param buffer Pointer to buffer containing the ICMP header.
 * @param buffer_len Length of the buffer in bytes.
 * @param header Output structure for parsed fields.
 * @return Number of bytes read, or a negative error code.
 */
int16_t icmp_header_parse(const uint8_t *buffer, uint8_t buffer_len, icmp_header_t *header);

int icmp_response_process(const uint8_t *transport, uint32_t ip_payload_len, const ip_header_t *ip_hdr);

#endif // ICMP_H