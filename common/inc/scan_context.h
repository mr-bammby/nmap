#ifndef SCAN_CONTEXT_H
#define SCAN_CONTEXT_H

#include "port_defines.h"

/* Define the range of ports to scan and the capacity for storing results. */
#define PORT_START 1
#define PORT_END PORT_MAX_PORT
#define RESULTS_CAPACITY PORT_NUMBER_OF_PORTS

/* Define a magic number for validating scan context cookies. */
#define COOKIE_MAGIC    0xA5UL
/* Macro for cookie creation. */
#define COOKIE_MAKE(scan_id, port) \
    ((COOKIE_MAGIC << 24) | (((uint32_t)(scan_id) & 0xF) << 20) | (((port) & 0xFFFF) << 4) | 0x0UL)
/* Macros for extracting scan type and port number from a cookie. */
#define COOKIE_SCAN(c)  (((c) >> 20) & 0x7)
#define COOKIE_PORT(c)  (((c) >> 4) & 0xFFFF)
#define COOKIE_VALID(c) (((c) >> 24) == COOKIE_MAGIC)

#endif /* SCAN_CONTEXT_H */