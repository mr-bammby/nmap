#include "argument_parser.h"
#include "address_utils.h"  /* common helpers for address handling */

parse_return_e argument_handler_address(params_t *param, const char *value)
{
    if (param->address != NULL)
    {
        return (PARSE_DOUBLE_VALUE);
    }
    if (parse_address_list(value, &(param->address)) != 0)
    {
        return (PARSE_BAD_VALUE);
    }
    return (PARSE_OK);
}
