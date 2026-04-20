#ifndef SCAN_CONTEXT_H
#define SCAN_CONTEXT_H

#include "response_states.h"

#define PORT_START 1
#define PORT_END 1024
#define RESULTS_CAPACITY 1024

extern scan_result_t results[RESULTS_CAPACITY];

#define COOKIE_MAGIC    0x1A5CUL
#define COOKIE_SCAN(c)  (((c) >> 13) & 0x7)
#define COOKIE_PORT(c)  ((c) & 0x1FFF)
#define COOKIE_VALID(c) (((c) >> 16) == COOKIE_MAGIC)

#endif // SCAN_CONTEXT_H