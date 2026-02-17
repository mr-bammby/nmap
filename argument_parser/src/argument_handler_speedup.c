#include "argument_parser.h"
#include <ctype.h>
#include <stdlib.h>

parse_return_e argument_handler_speedup(params_t *param, const char *value)
{
    /* the option takes a positive integer thread count */
    if (param->thread_num != 0)
        return PARSE_DOUBLE_VALUE;

    if (value == NULL || !isdigit((unsigned char)*value))
        return PARSE_BAD_VALUE;

    long val = strtol(value, NULL, 10);
    if (val <= 0 || val > UINT16_MAX)
        return PARSE_BAD_VALUE;

    param->thread_num = (uint16_t)val;
    return PARSE_OK;
}
