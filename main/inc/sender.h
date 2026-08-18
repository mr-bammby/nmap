#ifndef SENDER_H
#define SENDER_H

#include <stdint.h>
#include "response_states.h"

/* Initialize the sender */
int sender_init(int *sock_out);

/* Clean up the sender resources */
int sender_cleanup(int *sock);

/* Run the sender */
void sender_run(int sock, uint32_t target_ip, int port_i, uint32_t local_ip, uint8_t scan_flag, uint8_t probe, response_type_t *response_slot);

#endif /* SENDER_H */