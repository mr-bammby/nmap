#include "argument_parser.h"

parse_return_e argument_handler_help(params_t *param __attribute__((unused)), const char *value __attribute__((unused)))
{
    return PARSE_HELP_REQUEST;
}