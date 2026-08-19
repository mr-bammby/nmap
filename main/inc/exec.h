#ifndef _EXEC_H_
#define _EXEC_H_

#include "scan_defines.h"
#include "port_defines.h"
#include "argument_parser_types.h"
#include "protocol_ip.h"
#include "protocol_tcp.h"
#include "protocol_udp.h"
#include "scan_context.h"
#include <stdatomic.h>

extern atomic_bool interrupt_flag; /* Global flag to indicate an interrupt signal has been received */

int single_thread_exec(const char *target_ip, argparse_port_set_t ports, scan_bitmap_t scans, scan_result_t results[RESULTS_CAPACITY]);
void single_thread_cleanup(void);




#endif /* _EXEC_H_ */