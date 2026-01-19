#ifndef SCANS_H
#define SCANS_H

#include <arpa/inet.h> 
#include <inttypes.h>

#define NUMBER_OF_PORTS 1024

typedef uint8_t port_bitmap_t[NUMBER_OF_PORTS / 8];

// scan status codes shall only be expanded, never changed or removed
typedef enum 
{
    SCAN_SUCCESS = 0,
    SCAN_FAIL_GENERAL,
    SCAN_FAIL_NO_RESPONSE,
    // add more specific failure reasons as needed
} scan_status_t;


#endif // SCANS_H