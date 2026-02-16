#include "argument_parser.h"

parse_return_e argument_handler_help(params_t *param, const char *value)
{
    return PARSE_HELP_REQUEST;
}