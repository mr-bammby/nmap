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
        if ((params->scans & SCAN_FLG_SYN) != 0u)  { printf("SYN ");  }
        if ((params->scans & SCAN_FLG_NULL) != 0u) { printf("NULL "); }
        if ((params->scans & SCAN_FLG_FIN) != 0u)  { printf("FIN ");  }
        if ((params->scans & SCAN_FLG_XMAS) != 0u) { printf("XMAS "); }
        if ((params->scans & SCAN_FLG_ACK) != 0u)  { printf("ACK ");  }
        if ((params->scans & SCAN_FLG_UDP) != 0u)  { printf("UDP ");  }
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
    int i;
    uint8_t has_open = 0;
    uint8_t has_closed = 0;

    if (results != NULL)
    {
        printf("IP address: %s\n", target_ip);
        for (i = start; i < end; i++)
        {
            port_state_t current_state = rp_get_final_state(&results[i]);
            
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
            
            for (i = start; i < end; i++)
            {
                if (rp_get_final_state(&results[i]) == PORT_STATE_OPEN)
                {
                    rp_print_single_port_row(&results[i], GET_SERVICE_NAME(results[i].port));
                }
            }
        }

        if (has_closed)
        {
            printf("\nClosed/Filtered/Unfiltered ports:\n");
            printf("%-*s %-*s %-*s %s\n", RP_COL_WIDTH_PORT, "Port", RP_COL_WIDTH_SERVICE, "Service Name (if applicable)", RP_COL_WIDTH_RESULTS, "Results", "Conclusion");
            printf("------------------------------------------------------------------------------------------------------\n");
            
            for (i = start; i < end; i++)
            {
                port_state_t st = rp_get_final_state(&results[i]);
                
                if ((st != PORT_STATE_OPEN) && (st != PORT_STATE_NOT_SCANNED))
                {
                    rp_print_single_port_row(&results[i], GET_SERVICE_NAME(results[i].port));
                }
            }
        }
        printf("\n");
    }
}
