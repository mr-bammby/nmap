#ifndef __SENDER_H__
#define __SENDER_H__

#include "response_states.h"

#define RESPONSE_WAIT_ATTEMPTS 500
#define RESPONSE_POLL_SLEEP_US 1000

int sender_init(int *sock_out);
int sender_cleanup(int *sock);
void sender_run(int sock, const char *target_ip, int port_i, const char *local_ip, uint8_t scan_flag, uint8_t attempt, response_type_t *response_slot);

#endif /* __SENDER_H__ */