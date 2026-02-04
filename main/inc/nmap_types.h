#ifndef NMAP_TYPES_H
#define NMAP_TYPES_H

#include <inttypes.h>

#define SCAN_FLG_SYN    0x01
#define SCAN_FLG_NULL   0x02
#define SCAN_FLG_ACK    0x04
#define SCAN_FLG_FIN    0x08
#define SCAN_FLG_XMAS   0x10
#define SCAN_FLG_UDP    0x20

#define SCAN_FLG_ALL    0xff

#define BITMAP_BYTE_SIZE sizeof(uint8_t)

#define NUMBER_OF_PORTS 1024
#define PORT_BITMAP_BYTE_NUM NUMBER_OF_PORTS/BITMAP_BYTE_SIZE

typedef struct nmap_types
{
    char *addr;
    addr_node_t *next;
} addr_node_t;

typedef uint8_t port_bitmap_t[PORTMAP_BYTE_NUM];
typedef uint8_t scan_bitmap_t;
typedef *addr_node_t address_list_t;

#endif /* NMAP_TYPES_H */
