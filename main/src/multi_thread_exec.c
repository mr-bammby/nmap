#define MODULE_DEBUG DEBUG_MULTI_THREAD_EXEC
#include "debug.h"
#include "multi_thread_shared.h"
#include <pcap.h>
#include "receiver.h"
#include <stdlib.h>

uint8_t multi_thread_receiver_run(const argparse_params_t *params, const multi_thread_command_queue_state_t *last_queued_cmd, scan_result_t *results, uint32_t results_rows, uint32_t results_cols)
{

    size_t count = 0;
    char last_addr[16] = "\0";

    pcap_t *pcap_handle = NULL;
    int sock = -1;
    char *local_ip;
    uint32_t link_header_len;
    argparse_port_set_iterator_t port_it;
    unsigned int port_i;

    for (size_t i = 0; i < multi_thread_shared_cmd_queue.capacity; i++)
    {
        const multi_thread_command_t *command = &multi_thread_shared_cmd_queue.data[i];
        if (last_addr != command->address)
        {
            // Initialize receiver for specific address
            if (receiver_init(command->address, &port_it, &pcap_handle, &local_ip, &link_header_len) < 0)
            {
                LOGE("Failed to initialize receiver\n");

                return -1;
            }
            memcpy(last_addr, command->address, sizeof(command->address));
        }

        if (command->address[0] == '\0' && command->port == 0 && command->udp_flag_arr_idx == 0 && command->scan == 0)
        {
            break;
        }

        printf("[%zu] address=%s port=%u flag_idx=%u scan=0x%02x\n",
               i,
               command->address,
               command->port,
               command->udp_flag_arr_idx,
               command->scan);
        count++;
    }

    // Init pcap for sniffing
    // Move head/tail of queue to let sender threads start sending
    // Set Receiver timeout
    //while (1)
        // Start receiving
        // if receiver timeout reached
            // Q write suppressed part XXXXXXXXXX
        // if packet reveived
            // if udp
                // set udp flag in flagging array
            // write result
        // if cmd DONE sent
            // if #threads == 0
                // exit while
        
            
    // 
}

th_queue_t multi_thread_shared_cmd_queue = {0};
th_flagging_array_t multi_thread_shared_flagging_array = {0};


void multi_thread_exec(const argparse_params_t *params, scan_result_t **results, uint32_t results_rows, uint32_t results_cols)
{
    multi_thread_command_queue_state_t queue_state;
    //First entry in queue is special command for sleep 

    // if (multi_thread_init(params, &queue_state, results, results_rows, results_cols) != 0)
    // {
    //     return;
    // }
    //Start Sender Threads
    multi_thread_receiver_run(params, &queue_state, *results, results_rows, results_cols);

}