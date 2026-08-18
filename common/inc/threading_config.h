#ifndef THREADING_CONFIG_H
#define THREADING_CONFIG_H

#include <stdint.h>

/* Data structure for commands to be processed by worker threads. */
typedef struct multi_thread_command
{
    uint32_t address;
    uint16_t port;
    uint16_t udp_flag_arr_idx;
    uint16_t udp_flag_row_idx;
    uint8_t scan;
} multi_thread_command_t;

/* Type definition for the queue data type. */
#define TH_QUEUE_DATA_TYPE multi_thread_command_t

#endif /* THREADING_CONFIG_H */