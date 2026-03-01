#include <stdio.h>
#include <stdlib.h>
#include "argument_parser.h"
#include "nmap_types.h"

static const char *const valid_tokens[6] =
    {
        "SYN",
        "ACK",
        "NULL",
        "FIN",
        "XMAS",
        "UDP"};

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

void print_params(params_t *params)
{
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
    for (int i = 0; i < 1024; i++)
    {
        if (params->ports[i / 8] & (1 << (i % 8)))
        {
            printf("%u ", i);
        }
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

int main(int argc, const char *argv[])
{
    params_t params = {0};

    printf("NMAP Argument Parser - Test\n");
    printf("===========================\n");
    printf("Arguments: ");
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n\n");

    parse_return_e result = argument_parse(argc, argv, &params);

    printf("Parse Result: %s\n", parse_error_to_string(result));

    if (result == PARSE_OK)
    {
        print_params(&params);
    }
    else if (result == PARSE_HELP_REQUEST)
    {
        printf("\nHelp was requested.\n");
    }

    free_arguments(&params);

    return (result == PARSE_OK || result == PARSE_HELP_REQUEST) ? EXIT_SUCCESS : EXIT_FAILURE;
}