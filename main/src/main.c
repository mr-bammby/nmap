#include <stdio.h>
#include <stdlib.h>
#include "argument_parser.h"
#include "nmap_types.h"
#include "exec.h"
#include "port_utils.h"

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
    case PARSE_INTRNAL_ERROR:
        return "Internal error";
    default:
        return "Unknown error";
    }
}

void print_params(const params_t *params)
{
    port_set_iterator_t port_it;
    init_port_iterator(&port_it, &params->ports);

    printf("\nParsed Parameters:\n");
    printf("  Scans:");
    for (int i = 0; i < 6; i++)
    {
        if (params->scans & (1 << i))
        {
            printf(" %s", valid_tokens[i]);
        }
    }
    printf("\n");
    printf("  Ports: ");
    unsigned int port;
    while (port_iterator_next(&port_it, &port) == 0)
    {
        printf("%u ", port);
    }
    printf("\n");
    printf("  Threads: %u\n", params->thread_num);
    printf("  Addresses: ");

    addr_node_t *current = params->address;
    if (current == NULL)
    {
        printf("(none)");
    }
    else
    {
        int count = 0;
        while (current != NULL)
        {
            if (count > 0)
                printf(", ");
            printf("%s", current->addr);
            current = current->next;
            count++;
        }
    }
    printf("\n");
}

void main_argumnts(int argc, const char *argv[], parse_return_e ret, const params_t *params)
{
    printf("NMAP Argument Parser - Test\n");
    printf("===========================\n");
    printf("Arguments: ");
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n\n");

    printf("Parse Result: %s\n", parse_error_to_string(ret));

    if (ret == PARSE_OK)
    {
        print_params(params);
    }
    else if (ret == PARSE_HELP_REQUEST)
    {
        printf("\nHelp was requested.\n");
    }

    fflush(stdout);
}

int main(int argc, const char *argv[])
{
    params_t params = {0};

    parse_return_e parse_result = argument_parse(argc, argv, &params);
    int exec_result;

    #ifdef DEBUG_ARGUMENTS
    main_argumnts(argc, argv, parse_result, &params);
    #endif
    if (parse_result != PARSE_OK)
    {
        #ifndef DEBUG_ARGUMENTS
        main_argumnts(argc, argv, parse_result, &params);
        #endif
        if (parse_result == PARSE_HELP_REQUEST)
        {
            display_help();
            return EXIT_SUCCESS;
        }

        return EXIT_FAILURE;
    }
    else
    {
        if (params.thread_num > 1)
        {
            fprintf(stderr, "Multi-threading is not supported in current implementation.\n");
            return EXIT_FAILURE;
        }
        for (addr_node_t *current = params.address; current != NULL; current = current->next)
        {
            printf("Scanning %s...\n", current->addr);
            exec_result = single_thread_exec(current->addr, params.ports, params.scans);
            if (exec_result != 0)
            {
                fprintf(stderr, "Error scanning %s\n", current->addr);
            }
        }
    }

    free_arguments(&params);

    return (parse_result == PARSE_OK || parse_result == PARSE_HELP_REQUEST) ? EXIT_SUCCESS : EXIT_FAILURE;
}