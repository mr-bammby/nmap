#ifndef ICMP_H
#define ICMP_H

#include <inttypes.h>

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

#endif // ICMP_H