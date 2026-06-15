#ifndef _SCAN_PARSER_H_
#define _SCAN_PARSER_H_

#include "response_states.h"

port_state_t get_final_state(const scan_result_t *port_result);
const char *get_state_label(port_state_t port_result);

#endif /* _SCAN_PARSER_H_ */