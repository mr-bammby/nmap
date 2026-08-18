#ifndef PORT_MAP_H
#define PORT_MAP_H

#include <stdint.h>
#include <stddef.h>
#include "port_defines.h"

/* Structure representing a port payload */
typedef struct {
    const uint8_t *payload_data; // Pointer to the payload data
    const uint8_t len; // Smallest type for current list (< 256 bytes)
    const uint16_t src_port; // 0 if not port-specific
} port_payload_t;

/* Structure representing an entry in the port map */
typedef struct {
    uint16_t name_idx; // Index into the service names array
    uint8_t payload_idx; // Index into the port payloads array
} port_map_entry_t;

/* Declaration for service names. */
extern const char *const *service_names;

/* Declaration for port payloads. */
extern const port_payload_t *port_payloads;

/* Declaration for the port map. */
extern const port_map_entry_t *port_map;

/* Calculating the sizes of the payloads and service names arrays. */
#define MAX_PAYLOADS sizeof(PAYLOADS) / sizeof(port_payload_t)
#define MAX_PORT_NAME_IDX sizeof(SVC_NAMES) / sizeof(char *)

/* Retrieve service name and payload for a given port. */
#define GET_SERVICE_NAME(port) (service_names[port_map[port].name_idx])
#define GET_PAYLOAD(port) (port_payloads[port_map[port].payload_idx])

#endif /* PORT_MAP_H */