#define _GNU_SOURCE
#define MODULE_DEBUG DEBUG_ARGUMENT_HANDLER_SCANS
#include "debug.h"
#include "argument_parser.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define MAX_TOKENS 6

/* allowed scan type keywords; index corresponds to bit position in
   scan_bitmap_t */
static const char *const valid_tokens[MAX_TOKENS] =
    {
        "SYN",
        "NULL",
        "ACK",
        "FIN",
        "XMAS",
        "UDP"
    };

static parse_return_e parse_scan_tokens_to_bitmap(const char *input, scan_bitmap_t *bitmap)
{
    if (!input)
        return PARSE_BAD_VALUE;

    /* Make a copy since strtok modifies the string */
    char *input_copy = malloc(strlen(input) + 1);
    if (!input_copy)
        return PARSE_INTERNAL_ERROR;
    strcpy(input_copy, input);

    char *token = strtok(input_copy, ",");
    if (token == NULL)
    {
        free(input_copy);
        return PARSE_BAD_VALUE;
    }

    while (token != NULL)
    {
        /* compare token against known scan keywords */
        int i;
        for (i = 0; i < MAX_TOKENS; i++)
        {
            if (strcmp(token, valid_tokens[i]) == 0)
            {
                *bitmap |= (1 << i); // set bit
                break;
            }
        }
        if (i == MAX_TOKENS)
        {
            free(input_copy);
            return PARSE_BAD_VALUE;
        }
        token = strtok(NULL, ",");
    }

    free(input_copy);
    return PARSE_OK;
}

parse_return_e argument_handler_scan(params_t *param, const char *value)
{
    if (param->scans != 0)
        return PARSE_DOUBLE_VALUE;

    return parse_scan_tokens_to_bitmap(value, &(param->scans));
}
