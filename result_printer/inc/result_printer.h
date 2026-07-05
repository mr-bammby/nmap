#ifndef RESULT_PRINTER_H
#define RESULT_PRINTER_H

#include "argument_parser_types.h"
#include "response_states.h"

void resprint_print_scan_header(const argparse_params_t *params);
void resprint_parse_scan_results(const scan_result_t *results, int start, int end, const char *target_ip, double scan_time_s);

#endif /* RESULT_PRINTER_H */