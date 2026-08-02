#ifndef THREADING_CONFIG_H
#define THREADING_CONFIG_H

#include <stdint.h>

typedef struct multi_thread_command
{
    char address[16];
    uint16_t port;
    uint16_t udp_flag_arr_idx;
    uint16_t udp_flag_row_idx;
    uint8_t scan;
} multi_thread_command_t;

#define TH_QUEUE_DATA_TYPE multi_thread_command_t

#endif // THREADING_CONFIG_H