#ifndef NMAP_TYPES_H
#define NMAP_TYPES_H

#include <inttypes.h>
#include "port_defines.h"

typedef enum
{
    ARGPARSE_OK = 0,
    ARGPARSE_UNKNOWN_FLAG = 1,
    ARGPARSE_MISSING_VALUE = 2,
    ARGPARSE_BAD_VALUE = 3,
    ARGPARSE_HELP_REQUEST = 4,
    ARGPARSE_DOUBLE_VALUE = 5,
    ARGPARSE_FILE_ERROR = 6,
    ARGPARSE_INTERNAL_ERROR = 7
} argparse_return_e;

/* singly‑linked list node containing a fixed‑size IP string */
typedef struct argparse_addr_node
{
    char addr[16]; /* IPv4 string, "xxx.xxx.xxx.xxx" + NUL */
    struct argparse_addr_node *next;
} argparse_addr_node_t;

typedef struct
{
    unsigned int data[PORT_NUMBER_OF_PORTS];
    int count;
} argparse_port_set_t;

// The Iterator Structure
typedef struct {
    const argparse_port_set_t *set;
    int index;
} argparse_port_set_iterator_t;

typedef uint8_t scan_bitmap_t;
typedef argparse_addr_node_t *address_list_t;

#endif /* ARGUMENT_PARSER_TYPES_H */
