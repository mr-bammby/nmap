#ifndef SCAN_CONTEXT_H
#define SCAN_CONTEXT_H

#include "response_states.h"

#define PORT_START 1
#define PORT_END 150
#define RESULTS_CAPACITY 1024

extern scan_result_t results[RESULTS_CAPACITY];

#define COOKIE_MAGIC    0xA58UL
#define COOKIE_SCAN(c)  (((c) >> 16) & 0x7)
#define COOKIE_PORT(c)  ((c) & 0xFFFF)
#define COOKIE_VALID(c) (((c) >> 20) == COOKIE_MAGIC)

#endif // SCAN_CONTEXT_H