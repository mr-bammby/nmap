#ifndef NMAP_TYPES_H
#define NMAP_TYPES_H

#include <inttypes.h>

#define SCAN_FLG_SYN 0x01
#define SCAN_FLG_NULL 0x02
#define SCAN_FLG_ACK 0x04
#define SCAN_FLG_FIN 0x08
#define SCAN_FLG_XMAS 0x10
#define SCAN_FLG_UDP 0x20

#define SCAN_FLG_ALL 0xff
#define NUMBER_OF_PORTS 1024


/* singly‑linked list node containing a fixed‑size IP string */
typedef struct addr_node
{
    char addr[16]; /* IPv4 string, "xxx.xxx.xxx.xxx" + NUL */
    struct addr_node *next;
} addr_node_t;

typedef struct
{
    unsigned int data[NUMBER_OF_PORTS];
    int count;
} port_set_t;

// The Iterator Structure
typedef struct {
    const port_set_t *set;
    int index;
} port_set_iterator_t;

typedef uint8_t scan_bitmap_t;
typedef addr_node_t *address_list_t;

#endif /* NMAP_TYPES_H */
