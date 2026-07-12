#ifndef MULTI_THREAD_SHARED_H
#define MULTI_THREAD_SHARED_H


#include "argument_parser.h"
#include "argument_parser_port.h"
#include "response_states.h"
#include "th_queue.h"
#include "th_flagging_array.h"

#define MULTI_THREAD_SHARED_QUEUE_SIZE 1000
#define MULTI_THREAD_SHARED_FLAGGING_ARRAY_SIZE 1024

extern th_queue_t multi_thread_shared_cmd_queue;
extern th_flagging_array_t multi_thread_shared_flagging_array;

typedef struct multi_thread_command_queue_state
{
    uint32_t address_idx;
    uint16_t port_idx;
    uint8_t scan_idx;
} multi_thread_command_queue_state_t;


// HERE JUST FOR NOW SO WE HAVE STARTING POINT FOR MULTI-THREADING IMPLEMENTATION
uint8_t multi_thread_init(const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, scan_result_t **results, uint32_t results_rows, uint32_t results_cols);
uint8_t multi_thread_command_queue_init(const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, scan_result_t **results, uint32_t results_rows, uint32_t results_cols);

#endif // MULTI_THREAD_SHARED_H