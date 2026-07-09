#include "multi_thread_shared.h"
#include "th_queue.h"
#include "th_flagging_array.h"
#include "protocol_utils.h"
#include "scan_defines.h"

#include <string.h>

//TODO: Move to a more appropriate location.
typedef enum
{
    MULTI_TH_SP_CMD_SKIP = 0x80,
    MULTI_TH_SP_CMD_END = 0x81
} multi_thread_special_cmd_e;

static uint8_t add_scan_to_queue(const char *address, uint16_t port, uint16_t flag_arr_idx, uint8_t scan_flag)
{
    static uint32_t queue_idx = 0;

    if (queue_idx >= multi_thread_shared_cmd_queue.capacity)
    {
        return 2; // Queue is full
    }

    if (strncpy(multi_thread_shared_cmd_queue.data[queue_idx].address, address, sizeof(multi_thread_shared_cmd_queue.data[queue_idx].address) - 1) == NULL)
    {
        return 1;
    }
    multi_thread_shared_cmd_queue.data[queue_idx].port = port;
    multi_thread_shared_cmd_queue.data[queue_idx].udx_flag_arr_idx = flag_arr_idx;
    multi_thread_shared_cmd_queue.data[queue_idx].scan = scan_flag;
    queue_idx++;

    return 0;
}

static uint8_t add_sp_cmd_to_queue(multi_thread_special_cmd_e sp_cmd)
{
    if (sp_cmd != MULTI_TH_SP_CMD_SKIP && sp_cmd != MULTI_TH_SP_CMD_END)
    {
        return 1; // Invalid special command
    }

    return add_scan_to_queue("0.0.0.0", 0, 0, sp_cmd);
}

uint8_t multi_thread_init(const argparse_params_t *params, last_queued_cmd_t *last_queued_cmd, scan_result_t **results, uint32_t results_rows, uint32_t results_cols)
{
    // Initialize the command queue
    th_queue_init(&multi_thread_shared_cmd_queue, MULTI_THREAD_SHARED_QUEUE_SIZE);

    // Initialize the flagging array
    th_flagging_array_init(&multi_thread_shared_flagging_array, MULTI_THREAD_SHARED_FLAGGING_ARRAY_SIZE);

    // Initialize last queued command
    last_queued_cmd->address_idx = 0;
    last_queued_cmd->port_idx = 0;
    last_queued_cmd->scan_idx = 0;

    // Initialize results array
    for (uint32_t i = 0; i < results_rows; i++)
    {
        protocol_utils_initialize_results(results[i]);
    }

    argparse_port_set_iterator_t port_it;

    argparse_port_iterator_init(&port_it, params->ports);

    uint32_t done = 0;
    for (argparse_addr_node_t *current = params->address; current != NULL; current = current->next)
    {
        LOGD("Adding %s...\n", current->addr);
        uint8_t result = add_sp_cmd_to_queue(MULTI_TH_SP_CMD_SKIP); // Add a skip command to separate addresses
        if (result == 1)
        {
            LOGE("Failed to add skip command to queue for address %s\n", current->addr);
            return 1; // Error
        }
        else if (result == 2)
        {
            LOGE("Queue is full while adding skip command for address %s\n", current->addr);
            done = 1;
            break; // Queue is full, stop adding more commands
        }
        else
        {
            last_queued_cmd->port_idx = 0;
            last_queued_cmd->scan_idx = MULTI_TH_SP_CMD_SKIP;
        }
        while (argparse_port_iterator_next(&port_it, params->ports) == 0)
        {
            for (int scan_i = 0; scan_i < SCAN_NUMBER_OF_SCAN_TYPES; scan_i++)
            {
                if (params->scans & (1 << scan_i))
                {
                    uint8_t result = add_scan_to_queue(current->addr, params->ports.data[port_it.index - 1], port_it.index - 1, (uint8_t)(1u << scan_i));
                    if (result == 1)
                    {
                        LOGE("Failed to add scan command to queue for address %s\n", current->addr);
                        return 1; // Error
                    }
                    else if (result == 2)
                    {
                        LOGE("Queue is full while adding scan command for address %s\n", current->addr);
                        done = 1;
                        break; // Queue is full, stop adding more commands
                    }
                }
                last_queued_cmd->scan_idx = scan_i;
            }
            last_queued_cmd->port_idx++;
            if (done)
                break;
        }
        if (done)
            break;
        last_queued_cmd->address_idx++;
    }

    if (!done)
    {
        uint8_t result = add_sp_cmd_to_queue(MULTI_TH_SP_CMD_END); // Add an end command to signal completion
        if (result == 1)
        {
            LOGE("Failed to add end command to queue\n");
            return 1; // Error
        }
        else if (result == 2)
        {
            LOGE("Queue is full while adding end command\n");
            return 2; // Queue is full
        }
        else
        {
            last_queued_cmd->address_idx = 0;
            last_queued_cmd->port_idx = 0;
            last_queued_cmd->scan_idx = MULTI_TH_SP_CMD_END;
            LOGD("All commands added to queue successfully.\n");
        }

    }

    return 0; // Success
}