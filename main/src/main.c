#define MODULE_DEBUG DEBUG_MAIN
#include "debug.h"
// #define STRINGIFY2(x) #x
// #define STRINGIFY(x) STRINGIFY2(x)

// #pragma message("MODULE_DEBUG=" STRINGIFY(MODULE_DEBUG))
#include <stdio.h>
#include <stdlib.h>
#include "argument_parser.h"
#include "nmap_types.h"
#include "exec.h"
#include "port_utils.h"
#include "result_printer.h"
#include "scan_context.h"
#include "timer_utils.h"

static const char *const valid_tokens[6] =
    {
        "SYN",
        "ACK",
        "NULL",
        "FIN",
        "XMAS",
        "UDP"
    };

const char *parse_error_to_string(parse_return_e error)
{
    switch (error)
    {
    case PARSE_OK:
        return "OK";
    case PARSE_UNKNOWN_FLAG:
        return "Unknown flag";
    case PARSE_MISSING_VALUE:
        return "Missing value";
    case PARSE_BAD_VALUE:
        return "Bad value";
    case PARSE_HELP_REQUEST:
        return "Help requested";
    case PARSE_DOUBLE_VALUE:
        return "Duplicate value";
    case PARSE_FILE_ERROR:
        return "File error";
    case PARSE_INTERNAL_ERROR:
        return "Internal error";
    default:
        return "Unknown error";
    }
}

static void print_params(const params_t *params)
{
    port_set_iterator_t port_it;
    init_port_iterator(&port_it, &params->ports);
    LOGD("Parsed Parameters:\n");
    LOGD("\tScans:\n");
    for (int i = 0; i < 6; i++)
    {
        if (params->scans & (1 << i))
        {
            LOGD("\t\t%s\n", valid_tokens[i]);
      }
    }
    LOGD("\tPorts:\n");
    unsigned int port;
    int count = 0;
    while (port_iterator_next(&port_it, &port) == 0)
    {
        //LOGD("\t\t%u \n", port);
        if (count % 10 == 0)
            LOGD("\t\t%u", port);
        else
            LOGD_WF(", %u", port);
        count++;
    }
    LOGD_WF("\n");
    LOGD("\tThreads:\n");
    LOGD("\t\t%u\n", params->thread_num);

    LOGD("\tAddresses:\n");
    addr_node_t *current = params->address;
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

static void main_argumnts(int argc, const char *argv[], parse_return_e ret, const params_t *params)
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
    if (ret == PARSE_OK)
    {
        print_params(params);
    }
    else if (ret == PARSE_HELP_REQUEST)
    {
        LOGD("Help was requested.\n");
    }
    #endif /* DEBUG_MAIN */
}

int main(int argc, const char *argv[])
{
    params_t params = {0};

    parse_return_e parse_result = argument_parse(argc, argv, &params);
    int exec_result;

    #if DEBUG_MAIN
    main_argumnts(argc, argv, parse_result, &params);
    #endif /* DEBUG_MAIN */

    if (parse_result != PARSE_OK)
    {
        if (parse_result == PARSE_HELP_REQUEST)
        {
            display_help();
            return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
    }
    else
    {
        print_scan_header(&params);
        if (params.thread_num > 1)
        {
            LOGW("Multi-threading is not supported in current implementation.\n");
            return EXIT_FAILURE;
        }
        for (addr_node_t *current = params.address; current != NULL; current = current->next)
        {
            nmap_timer_t timer;
            float elapsed_time;
            scan_result_t results[RESULTS_CAPACITY];
            start_timer(&timer);
            LOGD("Scanning %s...\n", current->addr);
            exec_result = single_thread_exec(current->addr, params.ports, params.scans, results);
            if (exec_result != 0)
            {
                LOGE("Error scanning %s\n", current->addr);
            }
            stop_timer(&timer);
            elapsed_time = read_time_s(&timer);
            parse_scan_results(results, PORT_START - 1, PORT_END, current->addr, elapsed_time);
        }
    }

    free_arguments(&params);

    return (parse_result == PARSE_OK || parse_result == PARSE_HELP_REQUEST) ? EXIT_SUCCESS : EXIT_FAILURE;
}