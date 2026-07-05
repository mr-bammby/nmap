#define MODULE_DEBUG DEBUG_ARGUMENT_HANDLER_HELP
#include "debug.h"
#include "argument_parser.h"

argparse_return_e ap_handler_help(argparse_params_t *param __attribute__((unused)), const char *value __attribute__((unused)))
{
    return ARGPARSE_HELP_REQUEST;
}
