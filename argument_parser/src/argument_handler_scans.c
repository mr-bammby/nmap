#define _GNU_SOURCE
#include "argument_parser.h"
#include <string.h>
#include <stdlib.h>
#define MAX_TOKENS 6

/* allowed scan type keywords; index corresponds to bit position in
   scan_bitmap_t */
static const char *const valid_tokens[MAX_TOKENS] =
    {
        "SYN",
        "ACK",
        "NULL",
        "FIN",
        "XMAS",
        "UDP"
    };

uint8_t parse_scan_tokens_to_bitmap(const char *input, scan_bitmap_t *bitmap)
{
    if (!input)
        return 0;

    /* Make a copy since strtok modifies the string */
    char *input_copy = malloc(strlen(input) + 1);
    if (!input_copy)
        return -1;
    strcpy(input_copy, input);

    char *token = strtok(input_copy, ",");

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
            return (-1);
        }
        token = strtok(NULL, ",");
    }

    free(input_copy);
    return 0;
}

parse_return_e argument_handler_scan(params_t *param, const char *value)
{
    if (param->scans != 0)
        return (PARSE_DOUBLE_VALUE);
    if (parse_scan_tokens_to_bitmap(value, &(param->scans)) != 0)
    {
        return (PARSE_BAD_VALUE);
    }
    return (PARSE_OK);
}
