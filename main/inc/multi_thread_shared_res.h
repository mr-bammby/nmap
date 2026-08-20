#ifndef MULTI_THREAD_SHARED_RES_H
#define MULTI_THREAD_SHARED_RES_H


#include "argument_parser.h"
#include "argument_parser_port.h"
#include "response_states.h"
#include "th_queue.h"
#include "th_flagging_array.h"
#include <stdbool.h>
#include <stdatomic.h>
#include <pcap.h>
#include "addr_hashmap.h"

/* Global atomic flags for multi-threading control */
extern atomic_bool abort_flag; // Flag to signal threads to abort execution
extern atomic_int thread_counter;// Counter for active threads

/* Status codes for appending to the shared command queue */
typedef enum
{ 
    MULTI_TH_QUEUE_APPEND_ERR_INVALID_PARAM = -5, // terminate gracefully
    MULTI_TH_QUEUE_APPEND_ERR_LOCK  = -4, // terminate gracefully
    MULTI_TH_QUEUE_APPEND_OK_GENERIC = 0, // OK Status
    MULTI_TH_QUEUE_APPEND_ERR_FULL = -2, // stop filling (no successful write), marker full to be set
    MULTI_TH_QUEUE_APPEND_OK_FULL_AFTER = 3 //  stop filling (successful write), marker full to be set
} multi_thread_queue_append_status_t;

/* Shared resources for multi-threading */
#define MULTI_THREAD_SHARED_QUEUE_SIZE 1000
#define MULTI_THREAD_SHARED_FLAGGING_ARRAY_SIZE 1024

extern th_queue_t multi_thread_shared_cmd_queue;
extern th_flagging_array_t *multi_thread_shared_flagging_array;

/* Next scan to be processed of the multi-threaded command queue */
typedef struct multi_thread_command_queue_state
{
    uint16_t address_idx; // Index in the address list of the first scan not yet added to the queue
    uint16_t port_idx; // Index in the port list of the first scan not yet added to the queue
    uint8_t scan_idx; // Index of the first scan type not yet added to the queue
} multi_thread_command_queue_state_t;

/* Special commands for multi-threaded command queue */
typedef enum
{
    MULTI_TH_SP_CMD_SKIP = 0x80, // Special command to signal that the sender wait until the reciver removes the skip command from the queue and then continue processing
    MULTI_TH_SP_CMD_END = 0x81 // Special command to signal that the sender should terminate processing and exit
} multi_thread_special_cmd_e;

/* Initialization of the multi-threaded command queue */
uint8_t multi_thread_command_queue_init(const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, scan_result_t **results, uint32_t results_rows, uint32_t results_cols);

/* Add a scan to the multi-threaded command queue while threads are running */
uint8_t append_scan_receiver_run(const char *address_str, uint16_t flag_row_idx, uint16_t port, uint16_t flag_arr_idx, uint8_t scan_flag, th_queue_access_t *access);

/* Add a special command to the multi-threaded command queue while threads are running */
uint8_t append_special_receiver_run(multi_thread_special_cmd_e sp_cmd, th_queue_access_t *access);

#endif /* MULTI_THREAD_SHARED_RES_H */