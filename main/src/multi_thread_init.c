#define MODULE_DEBUG DEBUG_MULTI_THREAD_INIT
#include "debug.h"
#include "multi_thread_shared.h"
#include "th_queue.h"
#include "th_flagging_array.h"
#include "protocol_utils.h"
#include <arpa/inet.h>

#define HASH_MAP_SIZE_MULTIPLICATOR 10

uint8_t multi_thread_init(const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, scan_result_t **results, uint32_t results_rows, uint32_t results_cols, addr_hashmap_t *hash_map)
{
    LOGD("Entering multi_thread_init\n");
    addr_hashmap_init(hash_map, results_rows * HASH_MAP_SIZE_MULTIPLICATOR, NULL);

    argparse_addr_node_t *address_p = NULL;
    for (address_p = params->address; address_p != NULL ;address_p = address_p->next)
    {
        LOGD("Adding address %s to hashmap\n", address_p->addr);
        addr_hashmap_put(hash_map, inet_addr(address_p->addr));
    }
    th_queue_init(&multi_thread_shared_cmd_queue, MULTI_THREAD_SHARED_QUEUE_SIZE);

    /* Allocate an array of flagging arrays, one per results row (address) */
    multi_thread_shared_flagging_array = malloc(sizeof(th_flagging_array_t) * results_rows);
    if (!multi_thread_shared_flagging_array)
    {
        LOGE("Failed to allocate multi_thread_shared_flagging_array\n");
        return 1;
    }

    for (uint32_t i = 0; i < results_rows; i++)
    {
        /* Initialize each flagging array for the row with capacity = results_cols */
        th_flagging_array_init(&multi_thread_shared_flagging_array[i], results_cols);
        protocol_utils_initialize_results(results[i]);
    }
    LOGD("Multi-threading initialized: Command queue and flagging array set up, results array initialized.\n");
    return multi_thread_command_queue_init(params, queue_state, results, results_rows, results_cols);
}
