#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "response_states.h"

/* Functions to determine the final port state based on scan results. */
port_state_t rp_get_final_state(const scan_result_t *port_result);
port_state_t rp_get_syn_state(const scan_result_t *port_result);
port_state_t rp_get_ack_state(const scan_result_t *port_result);
port_state_t rp_get_null_state(const scan_result_t *port_result);
port_state_t rp_get_fin_state(const scan_result_t *port_result);
port_state_t rp_get_xmas_state(const scan_result_t *port_result);
port_state_t rp_get_udp_state(const scan_result_t *port_result);


#endif /* PARSER_UTILS_H */