#ifndef RESULT_PRINTER_H
#define RESULT_PRINTER_H

#include "argument_parser_types.h"
#include "response_states.h"

/* Print the header for the scan results table. */
void resprint_print_scan_header(const argparse_params_t *params);

/* Parse and print the scan results for a given range of ports. */
void resprint_parse_scan_results(const scan_result_t *results, int start, int end, const char *target_ip, double scan_time_s);

/* Print the scan statistics, including total time taken for the scan. */
void resprint_print_scan_stats(double scan_time_s);

#endif /* RESULT_PRINTER_H */