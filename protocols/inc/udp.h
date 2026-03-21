#ifndef UDP_H
#define UDP_H

#include <inttypes.h>

/* Error codes */
#define UDP_ERR_BUFFER_TOO_SMALL -1
#define UDP_ERR_CHECKSUM -2
#define UDP_ERR_INVALID_ARGUMENT -3

/**
 * UDP Header structure
 *
 * @param src_port Source port number
 * @param dst_port Destination port number
 * @param length Length of the UDP packet (including header and data)
 * @param checksum Checksum of the UDP packet
 */
typedef struct {
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t length;
    uint16_t checksum;
} udp_header_t;

/**
* Create a UDP header in the provided buffer.
*
* @param buffer Pointer to the buffer where the UDP header will be created.
* @param buffer_len Length of the buffer in bytes.
* @param header Pointer to the udp_header_t structure containing header fields.
* @return Number of bytes written to the buffer, or a negative error code.
*/
int16_t udp_header_create(uint8_t *buffer, uint8_t buffer_len, const udp_header_t *header);

/**
* Parse a UDP header from the provided buffer.
*
* @param buffer Pointer to the buffer containing the UDP header.
* @param buffer_len Length of the buffer in bytes.
* @param header Pointer to the udp_header_t structure where parsed fields will be stored.
* @return Number of bytes read from the buffer, or a negative error code.
*/
int16_t udp_header_parse(const uint8_t *buffer, uint8_t buffer_len, udp_header_t *header);

#endif // UDP_H