#ifndef RESULT_PRINTER_H
#define RESULT_PRINTER_H

#include "argument_parser.h"
#include "response_states.h"

void print_scan_header(const params_t *params);
void parse_scan_results(const scan_result_t *results, int start, int end, const char *target_ip, double scan_time_s);

#endif /* RESULT_PRINTER_H */