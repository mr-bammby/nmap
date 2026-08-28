#define MODULE_DEBUG DEBUG_ARGUMENT_HANDLER_SPEEDUP
#include "debug.h"
#include "argument_parser.h"
#include <ctype.h>
#include <stdlib.h>

#define MAX_THREAD_NUM 250


argparse_return_e ap_handler_speedup(argparse_params_t *param, const char *value)
{
    /* the option takes a positive integer thread count */
    if (param->thread_num != 0)
        return ARGPARSE_DOUBLE_VALUE;

    if (value == NULL || !isdigit((unsigned char)*value))
        return ARGPARSE_BAD_VALUE;

    long val = strtol(value, NULL, 10);
    if (val < 0 || val > MAX_THREAD_NUM)
        return ARGPARSE_BAD_VALUE;

    param->thread_num = (uint16_t)val + 1;
    return ARGPARSE_OK;
}
