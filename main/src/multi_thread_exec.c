#include "multi_thread_shared.h"

th_queue_t multi_thread_shared_cmd_queue = {0};
th_flagging_array_t multi_thread_shared_flagging_array = {0};


void multi_thread_exec(const argparse_params_t *params, scan_result_t **results, uint32_t results_rows, uint32_t results_cols)
{
    multi_thread_command_queue_state_t queue_state;

    if (multi_thread_init(params, &queue_state, results, results_rows, results_cols) != 0)
    {
        return;
    }
}