#include "multi_thread_shared.h"

uint8_t multi_thread_receiver_run(const argparse_params_t *params, const multi_thread_command_queue_state_t *last_queued_cmd, scan_result_t *results, uint32_t results_rows, uint32_t results_cols)
{
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

    if (multi_thread_init(params, &queue_state, *results, results_rows, results_cols) != 0)
    {
        return;
    }
    //Start Sender Threads
    multi_thread_receiver_run(params, &queue_state, *results, results_rows, results_cols);

}