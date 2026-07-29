#define MODULE_DEBUG DEBUG_MULTI_THREAD_INIT
#include "debug.h"
#include "multi_thread_shared.h"
#include "th_queue.h"
#include "th_flagging_array.h"
#include "protocol_utils.h"

uint8_t multi_thread_init(const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, scan_result_t **results, uint32_t results_rows, uint32_t results_cols)
{

    th_queue_init(&multi_thread_shared_cmd_queue, MULTI_THREAD_SHARED_QUEUE_SIZE);
    th_flagging_array_init(&multi_thread_shared_flagging_array, MULTI_THREAD_SHARED_FLAGGING_ARRAY_SIZE);

    scan_result_t *result_itr = results;
    for (uint32_t i = 0; i < results_rows; i++)
    {
        protocol_utils_initialize_results(result_itr);
        result_itr += results_cols;
    }
    LOGD("Multi-threading initialized: Command queue and flagging array set up, results array initialized.\n");
    return multi_thread_command_queue_init(params, queue_state, results, results_rows, results_cols);
}
