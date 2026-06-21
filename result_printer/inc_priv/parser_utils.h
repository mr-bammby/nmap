#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "response_states.h"

port_state_t get_final_state(const scan_result_t *port_result);
port_state_t get_syn_state(const scan_result_t *port_result);
port_state_t get_ack_state(const scan_result_t *port_result);
port_state_t get_null_state(const scan_result_t *port_result);
port_state_t get_fin_state(const scan_result_t *port_result);
port_state_t get_xmas_state(const scan_result_t *port_result);
port_state_t get_udp_state(const scan_result_t *port_result);


#endif /* PARSER_UTILS_H */