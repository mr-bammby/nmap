#ifndef _EXEC_H_
#define _EXEC_H_

#include "scan_defines.h"
#include "port_defines.h"
#include "argument_parser.h"
#include "argument_parser_types.h"
#include "protocol_ip.h"
#include "protocol_tcp.h"
#include "protocol_udp.h"
#include "scan_context.h"
#include <stdatomic.h>

/* Global flag to indicate an interrupt signal has been received */
extern atomic_bool interrupt_flag;

/* Single-threaded execution of scanning */
int single_thread_exec(const char *target_ip, argparse_port_set_t ports, scan_bitmap_t scans, scan_result_t results[RESULTS_CAPACITY]);

/* Cleanup of single-threading resources */
void single_thread_cleanup(void);

/* Multi-threaded execution of scanning */
uint8_t multi_thread_exec(const argparse_params_t *params, scan_result_t **results, uint32_t results_rows, uint32_t results_cols);

/* Cleanup of multi-threading resources */
void multi_thread_cleanup(void);

#endif /* _EXEC_H_ */