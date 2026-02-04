#include "argument_parser.h"

parse_return_e speedup_handler(params_t *param, const char *value)
{
    if (param->thread_num != 0)
        return (PARSE_DOUBLE_VALUE);
    if (isdigit(value) == 0)
        return (PARSE_BAD_VALUE);
    param->thread_num = atoi(value);

    return (PARSE_OK);
}
