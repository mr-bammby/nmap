#ifndef PRINTER_UTILS_H
#define PRINTER_UTILS_H

#include "argument_parser.h"
#include "response_states.h"

#define RP_COL_WIDTH_PORT      9
#define RP_COL_WIDTH_SERVICE   28
#define RP_COL_WIDTH_RESULTS   45
#define RP_COL_WIDTH_PAD       (RP_COL_WIDTH_PORT + 1 + RP_COL_WIDTH_SERVICE) /* 38 */


void rp_print_address_helper(const char *prefix, const address_list_t address);
const char *rp_get_state_label(port_state_t port_result);
void rp_print_single_port_row(const scan_result_t *res, const char *service_name);


#endif /* PRINTER_UTILS_H */