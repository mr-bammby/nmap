#ifndef RESPONSE_STATES_H
#define RESPONSE_STATES_H

#include <inttypes.h>

/* Port states from RFC or nmap conventions */
// typedef enum {
//     PORT_STATE_OPEN,           /* Port is accepting connections */
//     PORT_STATE_CLOSED,         /* Port is accessible but no service listening */
//     PORT_STATE_FILTERED,       /* Firewall/filter blocking access */
//     PORT_STATE_OPEN_FILTERED,  /* Can't determine (no response) */
//     PORT_STATE_UNFILTERED,     /* Accessible but open/closed unknown (ACK scan) */
//     PORT_STATE_UNKNOWN         /* Scan failed or error */
// } port_state_t;

/* What caused us to determine this state */
typedef enum {
    RESPONSE_NOT_EXPECTED,        /* Initial state before scanning */
    RESPONSE_NO_RESPONSE,      /* Timeout, no reply */
    RESPONSE_SYN_ACK,          /* SYN scan: got SYN/ACK */
    RESPONSE_RST,              /* Got TCP RST packet */
    RESPONSE_ICMP_UNREACHABLE, /* ICMP dest/port unreachable */
    RESPONSE_ICMP_FILTERED,    /* ICMP unreachable code indicates filtering */
    RESPONSE_UDP_REPLY,        /* UDP scan: got UDP response */
    RESPONSE_ERROR             /* Local error (send failed, etc) */
} response_type_t;

/* Generic scan result for a single port */
typedef struct {
    uint16_t port;             /* Port number scanned */
    uint8_t protocol;          /* PROTOCOL_TCP or PROTOCOL_UDP */
    response_type_t response_syn;  /* What response led to this conclusion */
    response_type_t response_null; /* For NULL scan, what response we got (if any) */
    response_type_t response_ack; /* For ACK, what response we got (if any) */
    response_type_t response_fin; /* For FIN scan, what response we got (if any) */
    response_type_t response_xmas; /* For Xmas scan, what response we got (if any) */
    response_type_t response_udp;  /* For UDP, what response we got (if any) */
} scan_result_t;

#endif // RESPONSE_STATES_H