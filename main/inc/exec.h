#ifndef _EXEC_H_
#define _EXEC_H_

#include "nmap_types.h"

int single_thread_exec(const char *target_ip, port_bitmap_t ports, scan_bitmap_t scans);

#endif /* _EXEC_H_ */