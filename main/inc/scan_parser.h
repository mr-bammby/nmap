#ifndef _SCAN_PARSER_H_
#define _SCAN_PARSER_H_

#include "response_states.h"

port_state_t final_result_logic(const scan_result_t *port_result);
const char *state_label_final(port_state_t port_result);

#endif /* _SCAN_PARSER_H_ */