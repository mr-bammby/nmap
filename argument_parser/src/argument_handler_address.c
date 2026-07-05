#define MODULE_DEBUG DEBUG_ARGUMENT_HANDLER_ADRESS
#include "debug.h"
#include "argument_parser.h"
#include "address_utils.h"
#include <stddef.h>  /* common helpers for address handling */
#include <stdio.h>


argparse_return_e ap_handler_address(argparse_params_t *param, const char *value)
{
    if (param->address != NULL)
    {
        return ARGPARSE_DOUBLE_VALUE;
    }
    return ap_address_parse_list(value, &(param->address));
}
