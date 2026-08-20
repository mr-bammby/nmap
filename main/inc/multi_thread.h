#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H
#include "multi_thread_shared_res.h"

/* Arguments for the multi-threaded sender thread */
typedef struct mult_thread_sender_args
{
    th_queue_t *cmd_queue; // Pointer to the shared command queue
    th_flagging_array_t *flagging_array; // Pointer to the shared flagging array
    uint16_t thread_id; // Unique identifier for the sender thread
    uint32_t local_ip; // Local IP address used for sending packets
} multithread_sender_args_t;

/* Initialization of multi-threading execution */
uint8_t multi_thread_init(const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, scan_result_t **results, uint32_t results_rows, uint32_t results_cols, addr_hashmap_t *hash_map);

/* Initialization of multi-threading receiver */
int multi_thread_receiver_init(const argparse_addr_node_t *addresses, pcap_t **pcap_handle_out, char **local_ip_out, uint32_t *link_header_len_out);

/* Multi-threaded execution of scanning */
uint8_t multi_thread_receiver_run(pcap_t *pcap_handle, uint32_t link_header_len, scan_result_t **results, addr_hashmap_t *hash_map, th_queue_access_t *access, const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, uint32_t results_rows, uint32_t results_cols);

/* Multi-threaded sender execution(thread function) */
void *multi_thread_sender(void *arg);

#endif /* MULTI_THREAD_H */