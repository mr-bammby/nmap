#define _GNU_SOURCE
#define MODULE_DEBUG DEBUG_ARGUMENT_HANDLER_SCANS
#include "debug.h"
#include "argument_parser.h"
#include "scan_defines.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define MAX_TOKENS 6

static argparse_return_e parse_scan_tokens_to_bitmap(const char *input, scan_bitmap_t *bitmap)
{
    if (!input)
        return ARGPARSE_BAD_VALUE;

    /* Make a copy since strtok modifies the string */
    char *input_copy = malloc(strlen(input) + 1);
    if (!input_copy)
        return ARGPARSE_INTERNAL_ERROR;
    strcpy(input_copy, input);

    char *token = strtok(input_copy, ",");
    if (token == NULL)
    {
        free(input_copy);
        return ARGPARSE_BAD_VALUE;
    }

    while (token != NULL)
    {
        /* compare token against known scan keywords */
        int i;
        for (i = 0; i < SCAN_NUMBER_OF_SCAN_TYPES; i++)
        {
            if (strcmp(token, scan_valid_tokens[i]) == 0)
            {
                *bitmap |= (1 << i); // set bit
                break;
            }
        }
        if (i == SCAN_NUMBER_OF_SCAN_TYPES)
        {
            free(input_copy);
            return ARGPARSE_BAD_VALUE;
        }
        token = strtok(NULL, ",");
    }

    free(input_copy);
    return ARGPARSE_OK;
}

argparse_return_e ap_handler_scan(argparse_params_t *param, const char *value)
{
    if (param->scans != 0)
        return ARGPARSE_DOUBLE_VALUE;

    return parse_scan_tokens_to_bitmap(value, &(param->scans));
}
