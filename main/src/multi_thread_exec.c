#include "multi_thread_shared.h"

static void multi_thread_receiver_run(params, &last_queued_cmd, results, results_rows, results_cols)
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

void multi_thread_exec(const argparse_params_t *params, scan_result_t **results, uint32_t results_rows, uint32_t results_cols)
{
    last_queued_cmd_t last_queued_cmd;
    //First entry in queue is special command for sleep 
    if (multi_thread_init(params, &last_queued_cmd) != 0)
    {
        return;
    }
    //Start Sender Threads
    multi_thread_receiver_run(params, &last_queued_cmd, results, results_rows, results_cols);

}