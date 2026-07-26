#define MODULE_DEBUG DEBUG_MULTI_THREAD_INIT
#include "debug.h"
#include "multi_thread_shared.h"
#include "th_queue.h"
#include "th_flagging_array.h"
#include "protocol_utils.h"
#include "scan_defines.h"
#include "threading_config.h"


static void init_payload(multi_thread_command_t *command, const char *address, uint16_t port, uint16_t flag_arr_idx, uint8_t scan_flag)
{
    if (command == NULL)
    {
        return;
    }

    memset(command, 0, sizeof(*command));
    if (address != NULL)
    {
        strncpy(command->address, address, sizeof(command->address) - 1);
        command->address[sizeof(command->address) - 1] = '\0';
    }
    command->port = port;
    command->udp_flag_arr_idx = flag_arr_idx;
    command->scan = scan_flag;
}


static uint8_t append_scan(const char *address, uint16_t port, uint16_t flag_arr_idx, uint8_t scan_flag)
{
    static uint32_t queue_idx = 0;

    if (queue_idx >= multi_thread_shared_cmd_queue.capacity)
    {
        return 2; // Queue is full
    }

    multi_thread_command_t command;
    init_payload(&command, address, port, flag_arr_idx, scan_flag);
    multi_thread_shared_cmd_queue.data[queue_idx] = command;
    queue_idx++;
    multi_thread_shared_cmd_queue.tail++;
    return 0;
}

static uint8_t append_special(multi_thread_special_cmd_e sp_cmd)
{
    if (sp_cmd != MULTI_TH_SP_CMD_SKIP && sp_cmd != MULTI_TH_SP_CMD_END)
    {
        return 1; // Invalid special command
    }
    multi_thread_shared_cmd_queue.tail++;
    return append_scan("0.0.0.0", 0, 0, sp_cmd);
}

uint8_t multi_thread_command_queue_init(const argparse_params_t *params, multi_thread_command_queue_state_t *queue_state, scan_result_t **results, uint32_t results_rows, uint32_t results_cols)
{
    // Initialize last queued command
    queue_state->address_idx = 0;
    queue_state->port_idx = 0;
    queue_state->scan_idx = 0;

    multi_thread_shared_cmd_queue.is_empty = 0;
    argparse_port_set_iterator_t port_it;
    unsigned int port_value = 0;

    uint32_t done = 0;
    for (argparse_addr_node_t *current = params->address; current != NULL; current = current->next)
    {
        LOGD("Adding %s...\n", current->addr);
        #ifndef MULTITHREAD_SENDER_TEST_MODE
            uint8_t result = append_special(MULTI_TH_SP_CMD_SKIP); // Add a skip command to separate addresses
        if (result == 1)
        {
            LOGE("Failed to add skip command to queue for address %s\n", current->addr);
            return 1; // Error
        }
        else if (result == 2)
        {
            LOGE("Queue is full while adding skip command for address %s\n", current->addr);
            done = 1;
            multi_thread_shared_cmd_queue.is_full = 1;
            break; // Queue is full, stop adding more commands
        }
        else
        #endif /* !defined(MULTI_TH_SP_CMD_SKIP) */
        {
            queue_state->port_idx = 0;
            queue_state->scan_idx = MULTI_TH_SP_CMD_SKIP;
            argparse_port_iterator_init(&port_it, &params->ports);
        }
        while (argparse_port_iterator_next(&port_it, &port_value) == 0)
        {
            for (int scan_i = 0; scan_i < SCAN_NUMBER_OF_SCAN_TYPES; scan_i++)
            {
                if (params->scans & (1 << scan_i))
                {
                    uint8_t result = append_scan(current->addr, (uint16_t)port_value, (uint16_t)port_it.index - 1, (uint8_t)(1u << scan_i));
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
                queue_state->scan_idx = scan_i;
            }
            queue_state->port_idx++;
            if (done)
                break;
        }
        if (done)
            break;
        queue_state->address_idx++;
    }

    if (!done)
    {
        uint8_t result = append_special(MULTI_TH_SP_CMD_END); // Add an end command to signal completion
        if (result == 1)
        {
            LOGE("Failed to add end command to queue\n");
            return 1; // Error
        }
        else if (result == 2)
        {
            LOGE("Queue is full while adding end command\n");
            multi_thread_shared_cmd_queue.is_full = 1;
            return 2; // Queue is full
        }
        else
        {
            queue_state->address_idx = 0;
            queue_state->port_idx = 0;
            queue_state->scan_idx = MULTI_TH_SP_CMD_END;
            LOGD("All commands added to queue successfully.\n");
        }

    }

    return 0; // Success
}