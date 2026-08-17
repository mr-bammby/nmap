#ifndef SCAN_CONTEXT_H
#define SCAN_CONTEXT_H

#include "port_defines.h"

#define PORT_START 1
#define PORT_END 65535
#define RESULTS_CAPACITY PORT_NUMBER_OF_PORTS


#define COOKIE_MAGIC    0xA58UL
#define COOKIE_SCAN(c)  (((c) >> 16) & 0x7)
#define COOKIE_PORT(c)  ((c) & 0xFFFF)
#define COOKIE_VALID(c) (((c) >> 20) == COOKIE_MAGIC)

#endif // SCAN_CO