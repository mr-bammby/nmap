#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argument_parser.h"
#include "multi_thread_shared.h"
#include "scan_context.h"

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

static void print_queue_contents(void)
{
    size_t count = 0;

    printf("Queue capacity: %zu\n", multi_thread_shared_cmd_queue.capacity);
    printf("Queue contents:\n");

    for (size_t i = 0; i < multi_thread_shared_cmd_queue.capacity; i++)
    {
        const multi_thread_command_t *command = &multi_thread_shared_cmd_queue.data[i];
        if (command->address[0] == '\0' && command->port == 0 && command->udx_flag_arr_idx == 0 && command->scan == 0)
        {
            break;
        }

        printf("[%zu] address=%s port=%u flag_idx=%u scan=0x%02x\n",
               i,
               command->address,
               command->port,
               command->udx_flag_arr_idx,
               command->scan);
        count++;
    }

    printf("Queued entries: %zu\n", count);
}

int main(int argc, const char *argv[])
{
    argparse_params_t params = {0};
    argparse_return_e parse_result = argparse_parse_arguments(argc, argv, &params);

    printf("Multi-thread init test\n");
    printf("=====================\n");
    printf("Arguments:\n");
    for (int i = 1; i < argc; i++)
    {
        printf(" %s", argv[i]);
    }
    printf("\n\n");

    printf("Parse result: %s\n", parse_error_to_string(parse_result));
    if (parse_result != ARGPARSE_OK)
    {
        argparse_free_arguments(&params);
        return EXIT_FAILURE;
    }

    size_t address_count = 0;
    for (argparse_addr_node_t *current = params.address; current != NULL; current = current->next)
    {
        address_count++;
    }

    scan_result_t **results = calloc(address_count, sizeof(*results));
    if (results == NULL)
    {
        fprintf(stderr, "Failed to allocate result pointers\n");
        argparse_free_arguments(&params);
        return EXIT_FAILURE;
    }

    const uint32_t results_cols = PORT_END - PORT_START + 1;
    for (size_t i = 0; i < address_count; i++)
    {
        results[i] = calloc(results_cols, sizeof(*results[i]));
        if (results[i] == NULL)
        {
            fprintf(stderr, "Failed to allocate results for address %zu\n", i);
            for (size_t j = 0; j < i; j++)
            {
                free(results[j]);
            }
            free(results);
            argparse_free_arguments(&params);
            return EXIT_FAILURE;
        }
    }

    multi_thread_command_queue_state_t queue_state = {0};
    uint8_t init_result = multi_thread_init(&params, &queue_state, results, (uint32_t)address_count, results_cols);
    printf("Init result: %u\n", init_result);

    if (init_result == 0)
    {
        print_queue_contents();
    }

    for (size_t i = 0; i < address_count; i++)
    {
        free(results[i]);
    }
    free(results);
    argparse_free_arguments(&params);

    return init_result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
