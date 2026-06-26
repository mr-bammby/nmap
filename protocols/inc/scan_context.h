#ifndef SCAN_CONTEXT_H
#define SCAN_CONTEXT_H

#include "response_states.h"

#define PORT_START 1
#define PORT_END 1024
#define RESULTS_CAPACITY (PORT_END - PORT_START + 1)


#define COOKIE_MAGIC    0xA58UL
#define COOKIE_SCAN(c)  (((c) >> 16) & 0x7)
#define COOKIE_PORT(c)  ((c) & 0xFFFF)
#define COOKIE_VALID(c) (((c) >> 20) == COOKIE_MAGIC)

#endif // SCAN_CONTEXT_H