#include "multi_thread_shared.h"

void multi_thread_exec(const argparse_params_t *params, scan_result_t **results, uint32_t results_rows, uint32_t results_cols)
{
    last_queued_cmd_t last_queued_cmd;

    if (multi_thread_init(params, &last_queued_cmd) != 0)
    {
        return;
    }
    multi_thread_receiver_run(params, &last_queued_cmd, results, results_rows, results_cols);
}