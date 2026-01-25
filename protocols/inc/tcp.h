#ifndef TCP_H
#define TCP_H

#include <arpa/inet.h> 
#include <inttypes.h>

#define TCP_FLAG_FIN 0x01
#define TCP_FLAG_SYN 0x02
#define TCP_FLAG_RST 0x04
#define TCP_FLAG_PSH 0x08
#define TCP_FLAG_ACK 0x10
#define TCP_FLAG_URG 0x20
#define TCP_FLAG_ECE 0x40
#define TCP_FLAG_CWR 0x80

#define TCP_ERR_BUFFER_TOO_SMALL -1
#define TCP_ERR_CHECKSUM -2
#define TCP_ERR_INVALID_ARGUMENT -3

typedef struct {
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq_num;
    uint8_t flags;
} tcp_header_t;

int16_t tcp_header_create(uint8_t *buffer, uint8_t buffer_len, const tcp_header_t *header);
int16_t tcp_header_parse(const uint8_t *buffer, uint8_t buffer_len, tcp_header_t *header);

#endif // TCP_H