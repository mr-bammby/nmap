#define MODULE_DEBUG DEBUG_RESULT_PRINTER
#include "debug.h"
#include <stdio.h>
#include <stdint.h>
#include "port_defines.h"
#include "scan_defines.h"
#include "parser_utils.h"
#include "printer_utils.h"
#include "port_map.h"


void resprint_print_scan_header(const argparse_params_t *params)
{
    if ((params != NULL) && (params->address != NULL))
    {
        printf("Scan Configurations\n");
        rp_print_address_helper("Target Ip-Address : ", params->address);
        printf("No of Ports to scan : %u\n", params->ports.count);
        
        printf("Scans to be performed : ");
        for (int scan_idx = 0; scan_idx < SCAN_NUMBER_OF_SCAN_TYPES; scan_idx++)
        {
            if ((params->scans & (1u << scan_idx)) != 0u)
                printf("%s ", scan_valid_tokens[scan_idx]);
        }
        printf("\n");
        
        printf("No of threads : %u\n", (uint32_t)params->thread_num);
        printf("Scanning..\n");
        printf("...................\n");
    }
}

void resprint_print_scan_stats(double scan_time_s)
{
    printf("Scan took %.5f secs\n", scan_time_s);
}

void resprint_parse_scan_results(const scan_result_t *results, int start, int end, const char *target_ip, double scan_time_s)
{
    uint8_t has_open = 0;
    uint8_t has_closed = 0;

    if (results == NULL)
    {
        return;
    }

    printf("IP address: %s\n", target_ip);

    /* Determine if there are any open or closed ports within the requested range
       by scanning the results array directly. The results array has one entry
       per potential port slot and each entry's `.port` field is non-zero when
       that slot corresponds to an active scanned port. */
    for (int i = 0; i < PORT_NUMBER_OF_PORTS; i++)
    {
        const scan_result_t *port_result = &results[i];
        if (port_result->port == 0)
            continue; /* unused slot */

        if ((int)port_result->port < start || (int)port_result->port > end)
            continue;

        port_state_t current_state = rp_get_final_state(port_result);
        if (current_state == PORT_STATE_OPEN)
        {
            has_open = 1;
        }
        else if (current_state != PORT_STATE_NOT_SCANNED)
        {
            has_closed = 1;
        }
    }

    if (has_open)
    {
        printf("\nOpen ports:\n");
        printf("%-*s %-*s %-*s %s\n", RP_COL_WIDTH_PORT, "Port", RP_COL_WIDTH_SERVICE, "Service Name (if applicable)", RP_COL_WIDTH_RESULTS, "Results", "Conclusion");
        printf("------------------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < PORT_NUMBER_OF_PORTS; i++)
        {
            const scan_result_t *port_result = &results[i];
            if (port_result->port == 0)
                continue;
            if ((int)port_result->port < start || (int)port_result->port > end)
                continue;

            if (rp_get_final_state(port_result) == PORT_STATE_OPEN)
            {
                rp_print_single_port_row(port_result, GET_SERVICE_NAME(port_result->port));
            }
        }
    }

    if (has_closed)
    {
        printf("\nClosed/Filtered/Unfiltered ports:\n");
        printf("%-*s %-*s %-*s %s\n", RP_COL_WIDTH_PORT, "Port", RP_COL_WIDTH_SERVICE, "Service Name (if applicable)", RP_COL_WIDTH_RESULTS, "Results", "Conclusion");
        printf("------------------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < PORT_NUMBER_OF_PORTS; i++)
        {
            const scan_result_t *port_result = &results[i];
            if (port_result->port == 0)
                continue;
            if ((int)port_result->port < start || (int)port_result->port > end)
                continue;

            port_state_t st = rp_get_final_state(port_result);
            if ((st != PORT_STATE_OPEN) && (st != PORT_STATE_NOT_SCANNED))
            {
                rp_print_single_port_row(port_result, GET_SERVICE_NAME(port_result->port));
            }
        }
    }

    printf("\n");
}
