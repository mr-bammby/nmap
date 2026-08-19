#ifndef MULTI_THREAD_SHARED_H
#define MULTI_THREAD_SHARED_H


#include "argument_parser.h"
#include "argument_parser_port.h"
#include "response_states.h"
#include "th_queue.h"
#include "th_flagging_array.h"
#include <stdbool.h>
#include <stdatomic.h>
#include <pcap.h>
#include "addr_hashmap.h"

extern atomic_bool abort_flag;
extern atomic_int thread_counter;

typedef enum th_queue_append_status
{ 
    TH_QUEUE_APPEND_ERR_INVALID_PARAM = -5, // terminate gracefully
    TH_QUEUE_APPEND_ERR_LOCK  = -4, // terminate gracefully
    TH_QUEUE_APPEND_OK_GENERIC = 0, // OK Status
    TH_QUEUE_APPEND_ERR_FULL = -2, // stop filling (no successful write), marker full to be set
    TH_QUEUE_APPEND_OK_FULL_AFTER = 3 //  stop filling (successful write), marker full to be set
} th_queue_append_status_t;


#define MULTI_THREAD_SHARED_QUEUE_SIZE 1000
#define MULTI_THREAD_SHARED_FLAGGING_ARRAY_SIZE 1024

extern th_queue_t multi_thread_shared_cmd_queue;
extern th_flagging_array_t *multi_thread_shared_flagging_array;

typedef struct multi_thread_command_queue_state
{
    uint16_t address_idx;
    uint16_t port_idx;
    uint8_t scan_idx;
} multi_thread_command_queue_state_t;

typedef struct mult_thread_sender_args
{

    th_queue_t *cmd_queue;
    th_flagging_array_t *flagging_array;
    uint16_t thread_id;
} multithread_sender_args_t;

//TODO: Move to a more appropriate location.
typedef enum
{
    MULTI_TH_SP_CMD_SKIP = 0x80,
    MULTI_TH_SP_CMD_END = 0x81
} multi_thread_special_cmd_e;


// HERE JUST FOR NOW SO WE HAVE STARTING POINT FOR MULTI-THREADING IMPLEMENTATION
uint8_t multi_thread_init(const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, scan_result_t **results, uint32_t results_rows, uint32_t results_cols, addr_hashmap_t *hash_map);
uint8_t multi_thread_command_queue_init(const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, scan_result_t **results, uint32_t results_rows, uint32_t results_cols);
void multi_thread_exec(const argparse_params_t *params, scan_result_t **results, uint32_t results_rows, uint32_t results_cols);
int multi_thread_receiver_init(const argparse_addr_node_t *addresses, pcap_t **pcap_handle_out, char **local_ip_out, uint32_t *link_header_len_out);
uint8_t multi_thread_receiver_run(pcap_t *pcap_handle, uint32_t link_header_len, scan_result_t **results, addr_hashmap_t *hash_map, th_queue_access_t *access, const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, uint32_t results_rows, uint32_t results_cols);
uint8_t receiver_append_scan(const char *address_str, uint16_t flag_row_idx, uint16_t port, uint16_t flag_arr_idx, uint8_t scan_flag, th_queue_access_t *access);
void *multi_thread_sender(void *arg);
uint8_t append_special(multi_thread_special_cmd_e sp_cmd);
#endif // MULTI_THREAD_SHARED_H