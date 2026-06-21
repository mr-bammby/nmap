#define MODULE_DEBUG DEBUG_ARGUMENT_HANDLER_ADRESS
#include "debug.h"
#include "argument_parser.h"
#include "address_utils.h"
#include <stddef.h>  /* common helpers for address handling */
#include <stdio.h>


parse_return_e argument_handler_address(params_t *param, const char *value)
{
    if (param->address != NULL)
    {
        return PARSE_DOUBLE_VALUE;
    }
    return parse_address_list(value, &(param->address));
}
