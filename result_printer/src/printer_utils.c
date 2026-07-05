#define MODULE_DEBUG DEBUG_PRINTER_UTILS
#include "debug.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "port_map.h"
#include "argument_parser.h"
#include "response_states.h"
#include "printer_utils.h"
#include "parser_utils.h"
#include "scan_defines.h"


#define MAX_PRINT_TOKE_LEN 20u


void print_address_helper(const char *prefix, const address_list_t address)
{
    const argparse_addr_node_t *current = address;
    uint32_t count = 0u;
    int prefix_len;

    if ((prefix != NULL) && (current != NULL))
    {
        printf("%s", prefix);
        prefix_len = (int)strlen(prefix);

        while (current != NULL)
        {
            if ((count > 0u) && ((count % 3u) == 0u))
            {
                printf("\n%*s", prefix_len, "");
            }
            printf("%-16s ", current->addr);
            current = current->next;
            count++;
        }
        printf("\n");
    }
}

const char *get_state_label(port_state_t port_result)
{
    switch (port_result)
    {
    case PORT_STATE_OPEN:
        return "Open";
    case PORT_STATE_CLOSED:
        return "Closed";
    case PORT_STATE_FILTERED:
        return "Filtered";
    case PORT_STATE_OPEN_FILTERED:
        return "Open|Filtered";
    case PORT_STATE_UNFILTERED:
        return "Unfiltered";
    default:
        return "Unknown";
    }
}

static uint8_t collect_active_tokens(const scan_result_t *res, char tokens[6][32])
{
    port_state_t states[6];
    uint8_t cnt = 0u;

    states[0] = get_syn_state(res);
    states[1] = get_null_state(res);
    states[2] = get_fin_state(res);
    states[3] = get_xmas_state(res);
    states[4] = get_ack_state(res);
    states[5] = get_udp_state(res);

    for (uint8_t i = 0u; i < 6u; i++)
    {
        if (states[i] != PORT_STATE_NOT_SCANNED)
        {
            snprintf(tokens[cnt], MAX_PRINT_TOKE_LEN, "%s(%s)", scan_valid_tokens[i], get_state_label(states[i]));
            cnt++;
        }
    }
    return cnt;
}


static uint32_t pack_tokens_into_rows(const char tokens[6][32], uint32_t token_count, char rows[6][128])
{
    uint32_t row_count = 0u;
    uint32_t token_idx = 0u;

    if (token_count == 0u)
    {
        strcpy(rows[0], "");
        row_count = 1u;
    }
    else
    {
        while (token_idx < token_count)
        {
            /* Prime the current row with the next available token */
            strcpy(rows[row_count], tokens[token_idx]);
            token_idx++;

            /* Greedily pull more tokens into this line if they fit */
            while (token_idx < token_count)
            {
                size_t potential_len = strlen(rows[row_count]) + 1u + strlen(tokens[token_idx]);
                
                if (potential_len <= COL_WIDTH_RESULTS)
                {
                    strcat(rows[row_count], " ");
                    strcat(rows[row_count], tokens[token_idx]);
                    token_idx++;
                }
                else
                {
                    break; /* Stop filling this row; wraps to the next */
                }
            }
            row_count++;
        }
    }

    return row_count;
}


static void render_port_row_matrix(uint32_t port, const char *service_name, 
                                      const char rows[6][128], uint32_t row_count, 
                                      const char *final_str)
{
    const char *safe_service = (service_name != NULL) ? service_name : "Unassigned";

    for (uint32_t r = 0u; r < row_count; r++)
    {
        bool is_first_row = (r == 0u);
        bool is_last_row  = (r == (row_count - 1u));

        if (is_first_row && is_last_row)
        {
            printf("%-*u %-*s %-*s %s\n", COL_WIDTH_PORT, port, COL_WIDTH_SERVICE, safe_service, COL_WIDTH_RESULTS, rows[r], final_str);
        }
        else if (is_first_row)
        {
            printf("%-*u %-*s %-*s\n", COL_WIDTH_PORT, port, COL_WIDTH_SERVICE, safe_service, COL_WIDTH_RESULTS, rows[r]);
        }
        else if (is_last_row)
        {
            printf("%-*s %-*s %s\n", COL_WIDTH_PAD, "", COL_WIDTH_RESULTS, rows[r], final_str);
        }
        else
        {
            printf("%-*s %-*s\n", COL_WIDTH_PAD, "", COL_WIDTH_RESULTS, rows[r]);
        }                                       // Middle rows, just print the tokens
    }
}


void print_single_port_row(const scan_result_t *res, const char *service_name)
{
    if (res != NULL)
    {
        char tokens[6][32];
        char rows[6][128];
        

        uint32_t active_count = collect_active_tokens(res, tokens);
        
        uint32_t row_count = pack_tokens_into_rows(tokens, active_count, rows);
        
        const char *final_str = get_state_label(get_final_state(res));
        render_port_row_matrix((uint32_t)res->port, service_name, rows, row_count, final_str);
    }
}

