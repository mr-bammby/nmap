#ifndef TCP_H
#define TCP_H

#include <arpa/inet.h> 
#include <inttypes.h>

/* TCP Flag definitions */
#define TCP_FLAG_FIN 0x01
#define TCP_FLAG_SYN 0x02
#define TCP_FLAG_RST 0x04
#define TCP_FLAG_PSH 0x08
#define TCP_FLAG_ACK 0x10
#define TCP_FLAG_URG 0x20
#define TCP_FLAG_ECE 0x40
#define TCP_FLAG_CWR 0x80

/* Error codes */
#define TCP_ERR_BUFFER_TOO_SMALL -1
#define TCP_ERR_CHECKSUM -2
#define TCP_ERR_INVALID_ARGUMENT -3

/**
 * TCP Header structure
 * 
 * @param src_port Source port number
 * @param dst_port Destination port number
 * @param seq_num Sequence number
 * @param flags TCP flags
 */
typedef struct {
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq_num;
    uint8_t flags;
} tcp_header_t;

/**
* Create a TCP header in the provided buffer.
*
* @param buffer Pointer to the buffer where the TCP header will be created.
* @param buffer_len Length of the buffer in bytes.
* @param header Pointer to the tcp_header_t structure containing header fields.
* @return Number of bytes written to the buffer, or a negative error code.
*/
int16_t tcp_header_create(uint8_t *buffer, uint8_t buffer_len, const tcp_header_t *header);

/**
* Parse a TCP header from the provided buffer.
*
* @param buffer Pointer to the buffer containing the TCP header.
* @param buffer_len Length of the buffer in bytes.
* @param header Pointer to the tcp_header_t structure where parsed fields will be stored.
* @return Number of bytes read from the buffer, or a negative error code.
*/
int16_t tcp_header_parse(const uint8_t *buffer, uint8_t buffer_len, tcp_header_t *header);

#endif // TCP_H