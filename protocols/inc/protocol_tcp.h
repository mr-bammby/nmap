#ifndef TCP_H
#define TCP_H

#include <arpa/inet.h> 
#include <inttypes.h>
#include "protocol_ip.h"
#include "response_states.h"
#include "argument_parser_types.h"

/* TCP Flag definitions */
#define PROTOCOL_TCP_FLAG_FIN 0x01
#define PROTOCOL_TCP_FLAG_SYN 0x02
#define PROTOCOL_TCP_FLAG_RST 0x04
#define PROTOCOL_TCP_FLAG_PSH 0x08
#define PROTOCOL_TCP_FLAG_ACK 0x10
#define PROTOCOL_TCP_FLAG_URG 0x20
#define PROTOCOL_TCP_FLAG_ECE 0x40
#define PROTOCOL_TCP_FLAG_CWR 0x80

/* Error codes */
#define PROTOCOL_TCP_ERR_BUFFER_TOO_SMALL -1
#define PROTOCOL_TCP_ERR_CHECKSUM -2
#define PROTOCOL_TCP_ERR_INVALID_ARGUMENT -3

#define PROTOCOL_TCP_HEADER_SIZE 20

/* TCP Header structure */
typedef struct {
    uint16_t src_port; /* Source port number */
    uint16_t dst_port; /* Destination port number */
    uint32_t seq_num;  /* Sequence number */
    uint8_t flags;     /* TCP flags */
} protocol_tcp_header_t;

/**
* Create a TCP header in the provided buffer.
*
* @param buffer Pointer to the buffer where the TCP header will be created.
* @param buffer_len Length of the buffer in bytes.
* @param header Pointer to the protocol_tcp_header_t structure containing header fields.
* @return Number of bytes written to the buffer, or a negative error code.
*/
int16_t protocol_tcp_header_create(uint8_t *buffer, uint8_t buffer_len, const protocol_tcp_header_t *tcp_header, const protocol_ip_header_t *ip_header, const uint32_t *payload, uint16_t payload_len);
/**
* Parse a TCP header from the provided buffer.
*
* @param buffer Pointer to the buffer containing the TCP header.
* @param buffer_len Length of the buffer in bytes.
* @param header Pointer to the protocol_tcp_header_t structure where parsed fields will be stored.
* @return Number of bytes read from the buffer, or a negative error code.
*/
int16_t protocol_tcp_header_parse(const uint8_t *buffer, uint8_t buffer_len, protocol_tcp_header_t *header, const protocol_ip_header_t *ip_header);

/**
 * Process a TCP response packet and update scan results.
 *
 * @param transport Pointer to the transport layer data (TCP).
 * @param ip_payload_len Length of the IP payload in bytes.
 * @param ip_hdr Pointer to the parsed IP header.
 * @param results Pointer to the scan results structure to update.
 * @param ports Pointer to the set of ports being scanned.
 * @return 0 on success, or a negative error code on failure.
 */
int8_t protocol_tcp_response_process(const uint8_t *transport, uint32_t ip_payload_len, const protocol_ip_header_t *ip_hdr, scan_result_t *results, const argparse_port_set_t *ports);

#endif /* TCP_H */