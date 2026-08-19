#define MODULE_DEBUG DEBUG_MULTI_COMMAND_QUEUE
#include "debug.h"
#include "multi_thread_shared.h"
#include "th_queue.h"
#include "th_flagging_array.h"
#include "protocol_utils.h"
#include "scan_defines.h"
#include "scan_context.h"
#include "threading_config.h"
#include <arpa/inet.h>


static void init_queue_element(multi_thread_command_t *command, uint32_t address, uint16_t flag_row_idx, uint16_t port, uint16_t flag_arr_idx, uint8_t scan_flag)
{
    if (command == NULL)
    {
        return;
    }

    memset(command, 0, sizeof(multi_thread_command_t));
    command->address = address;
    command->udp_flag_row_idx = flag_row_idx;
    command->port = port;
    command->udp_flag_arr_idx = flag_arr_idx;
    command->scan = scan_flag;
}

uint8_t append_scan_receiver_run(const char *address_str, uint16_t flag_row_idx, uint16_t port, uint16_t flag_arr_idx, uint8_t scan_flag, th_queue_access_t *access)
{
    if (multi_thread_shared_cmd_queue.is_full)
    {
        LOGD("Queue is full on entering init_append_scan in receiver run with address %s and port %d and scan %d\n", address_str, port, scan_flag);
        return TH_QUEUE_APPEND_ERR_FULL; // Queue is full
    }

    uint32_t target_ip;
    if (address_str == NULL || inet_pton(AF_INET, address_str, &target_ip) != 1)
    {
        return TH_QUEUE_APPEND_ERR_INVALID_PARAM; // Invalid address
    }

    multi_thread_command_t command;
    init_queue_element(&command, target_ip, flag_row_idx, port, flag_arr_idx, scan_flag);

    size_t idx = multi_thread_shared_cmd_queue.tail;
    switch (th_queue_write(access, &command))
    {
    case TH_QUEUE_ERR_INVALID_PARAM:
        exit (TH_QUEUE_APPEND_ERR_INVALID_PARAM); //ToDo: terminate gracefully
    case TH_QUEUE_ERR_LOCK:
        exit (TH_QUEUE_APPEND_ERR_LOCK); //ToDo: terminate gracefully
    case TH_QUEUE_ERR_FULL:
        return (TH_QUEUE_APPEND_ERR_FULL); //ToDo: wait for 3 attempts and then terminate gracefully if unsuccessfull 
    default:
        break;
    }

    multi_thread_shared_cmd_queue.is_empty = 0;
    uint16_t ret = TH_QUEUE_APPEND_OK_GENERIC;
    size_t next_tail = idx + 1;
    if (next_tail >= multi_thread_shared_cmd_queue.capacity)
    {
        next_tail = 0;
    }
    if (next_tail == multi_thread_shared_cmd_queue.head)
    {
        multi_thread_shared_cmd_queue.is_full = 1;
        ret = TH_QUEUE_APPEND_OK_FULL_AFTER; //ToDo:  reset timer
    }
    multi_thread_shared_cmd_queue.tail = next_tail;
    LOGD("Return value of receiver append %d\n", ret);
    return ret;
}

static uint8_t init_append_scan(const char *address_str, uint16_t flag_row_idx, uint16_t port, uint16_t flag_arr_idx, uint8_t scan_flag)
{
    if (multi_thread_shared_cmd_queue.is_full)
    {
        LOGD("Queue is full on entering init_append_scan with address %s and port %d and scan %d\n", address_str, port, scan_flag);
        return 2; // Queue is full
    }

    uint32_t target_ip;
    if (address_str == NULL || inet_pton(AF_INET, address_str, &target_ip) != 1)
    {
        return 1; // Invalid address
    }

    multi_thread_command_t command;
    init_queue_element(&command, target_ip, flag_row_idx, port, flag_arr_idx, scan_flag);

    size_t idx = multi_thread_shared_cmd_queue.tail;
    multi_thread_shared_cmd_queue.data[idx] = command;
    multi_thread_shared_cmd_queue.is_empty = 0;

    size_t next_tail = idx + 1;
    if (next_tail >= multi_thread_shared_cmd_queue.capacity)
    {
        next_tail = 0;
    }
    if (next_tail == multi_thread_shared_cmd_queue.head)
    {
        multi_thread_shared_cmd_queue.is_full = 1;
    }
    multi_thread_shared_cmd_queue.tail = next_tail;
    return 0;
}

uint8_t append_special(multi_thread_special_cmd_e sp_cmd)
{
    if (sp_cmd != MULTI_TH_SP_CMD_SKIP && sp_cmd != MULTI_TH_SP_CMD_END)
    {
        return 1; // Invalid special command
    }
    return init_append_scan("0.0.0.0", 0, 0, 0, sp_cmd);
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

    append_special(MULTI_TH_SP_CMD_SKIP); // Add a skip command to signal waiting until receiver is intitalized

    uint32_t done = 0;
    for (argparse_addr_node_t *current = params->address; current != NULL; current = current->next)
    {
        LOGD("Adding %s...\n", current->addr);

        queue_state->port_idx = 0;
        queue_state->scan_idx = MULTI_TH_SP_CMD_SKIP;
        argparse_port_iterator_init(&port_it, &params->ports);

        while (argparse_port_iterator_next(&port_it, &port_value) == 0)
        {
            for (int scan_i = 0; scan_i < SCAN_NUMBER_OF_SCAN_TYPES; scan_i++)
            {
                if (params->scans & (1 << scan_i))
                {
                    /* Mark the results slot as attempted so lack of reply is recorded */
                    uint8_t scan_flag = (uint8_t)(1u << scan_i);
                    if (results != NULL && queue_state->address_idx < results_rows) {
                        scan_result_t *row = results[queue_state->address_idx];
                        if (row != NULL && port_value >= PORT_START && port_value <= PORT_END) {
                            int port_index = -1;
                            if (argparse_port_find(&params->ports, port_value, &port_index) == 0 && port_index >= 0) {
                                switch (scan_flag) {
                                    case SCAN_FLG_SYN:  row[port_index].response_syn  = RESPONSE_NO_RESPONSE; break;
                                    case SCAN_FLG_NULL: row[port_index].response_null = RESPONSE_NO_RESPONSE; break;
                                    case SCAN_FLG_ACK:  row[port_index].response_ack  = RESPONSE_NO_RESPONSE; break;
                                    case SCAN_FLG_FIN:  row[port_index].response_fin  = RESPONSE_NO_RESPONSE; break;
                                    case SCAN_FLG_XMAS: row[port_index].response_xmas = RESPONSE_NO_RESPONSE; break;
                                    case SCAN_FLG_UDP:  row[port_index].response_udp  = RESPONSE_NO_RESPONSE; break;
                                    default: break;
                                }
                            }
                        }
                    }

                    uint8_t result = init_append_scan(current->addr, queue_state->address_idx, (uint16_t)port_value, (uint16_t)port_it.index - 1, scan_flag);
                    if (result == 1)
                    {
                        LOGE("Failed to add scan command to queue for address %s\n", current->addr);
                        return 1; // Error
                    }
                    else if (result == 2)
                    {

                        LOGE("Queue is full while adding scan command for address %s\n", current->addr);
                        done = 1;
                        queue_state->scan_idx = scan_i;
                        break; // Queue is full, stop adding more commands
                    }
                }
                queue_state->scan_idx = scan_i;
            }
            if (done)
                break;
            queue_state->port_idx++;
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
            LOGI("Queue state after init: head=%zu tail=%zu is_empty=%u is_full=%u capacity=%zu\n", multi_thread_shared_cmd_queue.head, multi_thread_shared_cmd_queue.tail, multi_thread_shared_cmd_queue.is_empty, multi_thread_shared_cmd_queue.is_full, multi_thread_shared_cmd_queue.capacity);
        }

    }

    return 0; // Success
}