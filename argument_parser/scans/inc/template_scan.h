#ifndef TEMPLATE_SCAN_H
#define TEMPLATE_SCAN_H

#include <arpa/inet.h> 
#include <inttypes.h>
#include "scans.h"

// return type shall be modified per scan type
typedef struct 
{
    uint8_t success;
    uint8_t reason;
} template_scan_return_type_t;

scan_status_t template_scan(const char *target_ip, port_bitmap_t target_ports, uint8_t thread_count, template_scan_return_type_t *result);

#endif // TEMPLATE_SCAN_H