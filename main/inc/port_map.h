#ifndef PORT_MAP_H
#define PORT_MAP_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    const uint8_t *payload_data;
    const uint8_t len; // Smallest type for current list (< 256 bytes)
    const uint16_t src_port; // 0 if not port-specific
} port_payload_t;

typedef struct {
    uint16_t name_idx;
    uint8_t payload_idx; 
} port_map_entry_t;

extern const char *SVC_NAMES[];
extern const port_payload_t PAYLOADS[];
extern const port_map_entry_t PORT_MAP[65536];

#define MAX_PAYLOADS sizeof(PAYLOADS) / sizeof(port_payload_t)
#define MAX_PORT_NAME_IDX sizeof(SVC_NAMES) / sizeof(char *)

#endif // PORT_MAP_H