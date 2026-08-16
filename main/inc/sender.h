#ifndef __SENDER_H__
#define __SENDER_H__

#include <stdint.h>
#include "response_states.h"

#define UDP_PROBE_VARIANTS 3u
#define RESPONSE_POLL_SLEEP_US 1000

int sender_init(int *sock_out);
int sender_cleanup(int *sock);
void sender_run(int sock, uint32_t target_ip, int port_i, uint32_t local_ip, uint8_t scan_flag, uint8_t probe, response_type_t *response_slot);

#endif /* __SENDER_H__ */