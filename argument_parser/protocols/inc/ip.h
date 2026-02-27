#ifndef IP_H
#define IP_H

#include <inttypes.h>

#define VERSION_IPV4 4
#define PROTOCOL_ICMP 1
#define PROTOCOL_TCP 6
#define PROTOCOL_UDP 17

#define IP_MIN_HEADER_LEN 20

#define IP_DEFAULT_TOS 0
#define IP_DEFAULT_TTL 64
#define IP_DEFAULT_OFFSET 0x4000

#define IP_ERR_BUFFER_TOO_SMALL -1
#define IP_ERR_CHECKSUM -2
#define IP_ERR_INVALID_ARGUMENT -3


typedef struct ip_header {
    uint16_t id;                        /* identification */
    uint8_t  protocol;                  /* protocol */
    uint32_t src;                       /* source address */
    uint32_t dst;                       /* destination address */
} ip_header_t;

/**
 * Initialize an IP header in the provided buffer.
 *
 * @param buffer Pointer to the buffer where the IP header will be initialized.
 * @param buffer_len Length of the buffer in bytes.
 * @param header Pointer to the ip_header_t structure containing header fields.
 * @return Number of bytes written to the buffer, or a negative error code.
 */
int16_t ip_header_init(uint8_t *buffer, uint8_t buffer_len, const ip_header_t *header);

/**
 * Encapsulate the payload by finalizing the IP header (total length and checksum).
 *
 * @param buffer Pointer to the buffer containing the IP header.
 * @param payload_length Length of the payload in bytes.
 * @return Total packet length (IP header + payload), or a negative error code.
 */
int16_t ip_header_encapsulate(uint8_t *buffer, uint16_t payload_length);

/**
 * Parse an IP header from the provided buffer.
 *
 * @param buffer Pointer to the buffer containing the IP header.
 * @param buffer_len Length of the buffer in bytes.
 * @param header Pointer to the ip_header_t structure where parsed fields will be stored.
 * @return Number of bytes read from the buffer, or a negative error code.
 */
int16_t ip_header_parse(const uint8_t *buffer, uint8_t buffer_len, ip_header_t *header);

#endif // IP_H