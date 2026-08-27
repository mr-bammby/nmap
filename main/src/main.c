#define MODULE_DEBUG DEBUG_MAIN
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>
#include "argument_parser.h"
#include "scan_defines.h"
#include "argument_parser_port.h"
#include "argument_parser_types.h"
#include "result_printer.h"
#include "exec.h"
#include "scan_context.h"
#include "timer_utils.h"
#include "multi_thread_shared_res.h"
#include "signal_handler.h"
#include "version.h"

struct nmap_allocs
{
    argparse_params_t params;
    scan_result_t *results;
    scan_result_t **results_rows;
    pthread_t signal_handler_thread;
};

struct nmap_allocs g_allocs = { {0}, NULL, NULL, 0 };

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

atomic_bool interrupt_flag = false;

static const char *parse_error_to_string(argparse_return_e error)
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

/* Signal callback used by init_signal_handler -- must be async-signal-safe */
static void signal_callback(void)
{
    /* Set the global interrupt flag observed by threads */
    atomic_store(&interrupt_flag, true);
}

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

static void cleanup(void)
{
    /* Ensure signal waiter thread is shutdown before freeing resources */
    shutdown_signal_handler();
    LOGE("Cleaning up...\n");

    free(g_allocs.results_rows);
    g_allocs.results_rows = NULL;
    free(g_allocs.results);
    g_allocs.results = NULL;
    argparse_free_arguments(&g_allocs.params);
}


int main(int argc, const char *argv[])
{
    if (priv_test() != 0)
    {
        display_nopriv();
        return EXIT_FAILURE;
    }
    int exec_result;
    /* Register the full cleanup to be called directly from the signal handler */
    init_signal_handler(signal_callback);
    argparse_return_e parse_result = argparse_parse_arguments(argc, argv, &g_allocs.params);

    #if DEBUG_MAIN
    main_arguments(argc, argv, parse_result, &g_allocs.params);
    #endif /* DEBUG_MAIN */

    if (parse_result != ARGPARSE_OK)
    {
        if (parse_result == ARGPARSE_HELP_REQUEST)
        {
            display_help();
            cleanup();
            return EXIT_SUCCESS;
        }
        display_help();
        cleanup();
        return EXIT_FAILURE;
    }
    else
    {
        resprint_print_scan_header(&g_allocs.params);
        LOGD("Start counting addresses\n");
        int address_count = 0;
        for (argparse_addr_node_t *current = g_allocs.params.address; current != NULL; current = current->next)
        {
            LOGD("For loop address from current: %s\n", current->addr);
            address_count++;
        }
        LOGD("Address count: %d\n", address_count);
        g_allocs.results = calloc(sizeof(scan_result_t), RESULTS_CAPACITY * address_count);
        if (!g_allocs.results)
        {
            LOGE("Failed to allocate memory for scan results.\n");
            cleanup();
            return EXIT_FAILURE;
        }
        /* Restructure results into rows */
        g_allocs.results_rows  = malloc(address_count * sizeof(scan_result_t *));
        if (!g_allocs.results_rows)
        {
            LOGE("Failed to allocate memory for scan result row pointers.\n");
            free(g_allocs.results);
            cleanup();
            return EXIT_FAILURE;
        }
        for (int i = 0; i < address_count; i++)
        {
            g_allocs.results_rows[i] = &g_allocs.results[i * RESULTS_CAPACITY];
        }
        
        nmap_timer_t timer;
        float elapsed_time;
        start_timer(&timer);

        if (g_allocs.params.thread_num > 1)
        {
            LOGD("Multi threading starts\n");
            if (multi_thread_exec(&g_allocs.params, g_allocs.results_rows, address_count, RESULTS_CAPACITY) != 0)
            {
                LOGE("Error during multi-threaded execution\n");
                cleanup();
                return EXIT_FAILURE;
            }
        }
        else
        {
            uint32_t cnt = 0;
            for (argparse_addr_node_t *current = g_allocs.params.address; current != NULL; current = current->next)
            {
                LOGD("Scanning %s...\n", current->addr);
                /* Pass the per-address results block to single_thread_exec */
                exec_result = single_thread_exec(current->addr, g_allocs.params.ports, g_allocs.params.scans, g_allocs.results_rows[cnt]);
                if (exec_result != 0)
                {
                    LOGE("Error scanning %s\n", current->addr);
                    cleanup();
                    return EXIT_FAILURE;
                }
                cnt++;
            }
        }
        stop_timer(&timer);
        elapsed_time = read_time_s(&timer);
        
        resprint_print_scan_stats(elapsed_time);
        /* Print results per-address using the per-address block start */
        int idx = 0;
        for (argparse_addr_node_t *current = g_allocs.params.address; current != NULL; current = current->next)
        {
            resprint_parse_scan_results(&g_allocs.results[idx * RESULTS_CAPACITY], PORT_START - 1, PORT_END, current->addr, elapsed_time);
            idx++;
        }
    }
    cleanup();

    return (parse_result == ARGPARSE_OK || parse_result == ARGPARSE_HELP_REQUEST) ? EXIT_SUCCESS : EXIT_FAILURE;
}
