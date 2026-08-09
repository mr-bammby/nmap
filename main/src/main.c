#define MODULE_DEBUG DEBUG_MAIN
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "argument_parser.h"
#include "scan_defines.h"
#include "argument_parser_port.h"
#include "argument_parser_types.h"
#include "result_printer.h"
#include "exec.h"
#include "scan_context.h"
#include "timer_utils.h"
#include "multi_thread_shared.h"
#include "signal_handler.h"

const char *parse_error_to_string(argparse_return_e error)
{
    switch (error)
    {
    case ARGPARSE_OK:
        return "OK";
    case ARGPARSE_UNKNOWN_FLAG:
        return "Unknown flag";
    case ARGPARSE_MISSING_VALUE:
        return "Missing value";
    case ARGPARSE_BAD_VALUE:
        return "Bad value";
    case ARGPARSE_HELP_REQUEST:
        return "Help requested";
    case ARGPARSE_DOUBLE_VALUE:
        return "Duplicate value";
    case ARGPARSE_FILE_ERROR:
        return "File error";
    case ARGPARSE_INTERNAL_ERROR:
        return "Internal error";
    default:
        return "Unknown error";
    }
}

static void print_params(const argparse_params_t *params)
{
    argparse_port_set_iterator_t port_it;
    argparse_port_iterator_init(&port_it, &params->ports);
    LOGD("Parsed Parameters:\n");
    LOGD("\tScans:\n");
    for (int i = 0; i < SCAN_NUMBER_OF_SCAN_TYPES; i++)
    {
        if (params->scans & (1 << i))
        {
            LOGD("\t\t%s\n", scan_valid_tokens[i]);
      }
    }
    LOGD("\tPorts:\n");
    unsigned int port;
    int count = 0;
    while (argparse_port_iterator_next(&port_it, &port) == 0)
    {
        //LOGD("\t\t%u \n", port);
        if (count % 10 == 0)
            LOGD("\t\t%u", port);
        else if (count % 10 == 9)
            LOGD_WF(", %u\n", port);
        else
            LOGD_WF(", %u", port);

        count++;
    }
    LOGD_WF("\n");
    LOGD("\tThreads:\n");
    LOGD("\t\t%u\n", params->thread_num);

    LOGD("\tAddresses:\n");
    argparse_addr_node_t *current = params->address;
    if (current == NULL)
    {
        LOGE("(none)\n");
    }
    else
    {
        int count = 0;
        while (current != NULL)
        {
            if (count % 5 == 0)
                LOGD("\t\t%s", current->addr);
            else
                LOGD_WF(", %s", current->addr);
            current = current->next;
            count++;
        }
    }
    LOGD_WF("\n");
}

static void cleanup_on_interrupt(void);

static void main_arguments(int argc, const char *argv[], argparse_return_e ret, const argparse_params_t *params)
{
    LOGD("NMAP Argument Parser - Test\n");
    LOGD("===========================\n");
    LOGD("Arguments: \n");
    for (int i = 1; i <= argc - 1; i++)
    {
        if (i ==1)
            LOGD("%s ", argv[i]);
        else
            LOGD_WF("%s ", argv[i]);
    }
    LOGD_WF("\n\n");

    LOGD("Parse Result: %s\n", parse_error_to_string(ret));

    #if DEBUG_MAIN
    if (ret == ARGPARSE_OK)
    {
        print_params(params);
    }
    else if (ret == ARGPARSE_HELP_REQUEST)
    {
        LOGD("Help was requested.\n");
    }
    #endif /* DEBUG_MAIN */
}

static short priv_test(void)
{
    int s = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (s < 0)
    {
        return 1;
    }
    close(s);
    return 0;
}

static void cleanup_on_interrupt(void)
{
    fprintf(stderr, "Cleaning up...\n");
}

int main(int argc, const char *argv[])
{
    if (priv_test() != 0)
    {
        display_nopriv();
        return EXIT_FAILURE;
    }

    argparse_params_t params = {0};

    argparse_return_e parse_result = argparse_parse_arguments(argc, argv, &params);
    init_signal_handler(cleanup_on_interrupt);
    
    int exec_result;

    #if DEBUG_MAIN
    main_arguments(argc, argv, parse_result, &params);
    #endif /* DEBUG_MAIN */

    if (parse_result != ARGPARSE_OK)
    {
        if (parse_result == ARGPARSE_HELP_REQUEST)
        {
            display_help();
            return EXIT_SUCCESS;
        }
        display_help();
        return EXIT_FAILURE;
    }
    else
    {
        resprint_print_scan_header(&params);
        printf("TEST PRINTF AFTER HEADER PRINT\n");
        LOGD("Start counting addresses\n");
        int address_count = 0;
        for (argparse_addr_node_t *current = params.address; current != NULL; current = current->next)
        {
            LOGD("For loop address from current: %s\n", current->addr);
            address_count++;
        }
        LOGD("Address count: %d\n", address_count);
        scan_result_t *results = calloc(sizeof(scan_result_t), RESULTS_CAPACITY * address_count);
        if (!results)
        {
            LOGE("Failed to allocate memory for scan results.\n");
            argparse_free_arguments(&params);
            return EXIT_FAILURE;
        }

        /* Restructure results into rows */
        scan_result_t **results_rows = malloc(address_count * sizeof(scan_result_t *));
        if (!results_rows)
        {
            LOGE("Failed to allocate memory for scan result row pointers.\n");
            free(results);
            argparse_free_arguments(&params);
            return EXIT_FAILURE;
        }
        for (int i = 0; i < address_count; i++)
        {
            results_rows[i] = &results[i * RESULTS_CAPACITY];
        }
        
        nmap_timer_t timer;
        float elapsed_time;
        start_timer(&timer);

        if (params.thread_num > 1)
        {
            LOGD("Multi threading starts\n");
            multi_thread_exec(&params, results_rows, address_count, RESULTS_CAPACITY);
        }
        else
        {
            uint32_t cnt = 0;
            for (argparse_addr_node_t *current = params.address; current != NULL; current = current->next)
            {
                LOGD("Scanning %s...\n", current->addr);
                /* Pass the per-address results block to single_thread_exec */
                exec_result = single_thread_exec(current->addr, params.ports, params.scans, results_rows[cnt]);
                if (exec_result != 0)
                {
                    LOGE("Error scanning %s\n", current->addr);
                }
                cnt++;
            }
        }

        stop_timer(&timer);
        elapsed_time = read_time_s(&timer);
        
        resprint_print_scan_stats(elapsed_time);
        /* Print results per-address using the per-address block start */
        int idx = 0;
        for (argparse_addr_node_t *current = params.address; current != NULL; current = current->next)
        {
            resprint_parse_scan_results(&results[idx * RESULTS_CAPACITY], PORT_START - 1, PORT_END, current->addr, elapsed_time);
            idx++;
        }

        free(results_rows);
        free(results);
    }

    argparse_free_arguments(&params);

    return (parse_result == ARGPARSE_OK || parse_result == ARGPARSE_HELP_REQUEST) ? EXIT_SUCCESS : EXIT_FAILURE;
}