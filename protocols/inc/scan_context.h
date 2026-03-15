#ifndef SCAN_CONTEXT_H
#define SCAN_CONTEXT_H

#include "response_states.h"

#define PORT_START 1
#define PORT_END 150
#define RESULTS_CAPACITY 1024

extern scan_result_t results[RESULTS_CAPACITY];

#endif // SCAN_CONTEXT_H