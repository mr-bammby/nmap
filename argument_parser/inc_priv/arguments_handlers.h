#ifndef ARGUMENT_HANDLERS_H
#define ARGUMENT_HANDLERS_H

#include "nmap_types.h"

typedef enum
{
    PARSE_OK = 0,
    PARSE_UNKNOWN_FLAG = 1,
    PARSE_MISSING_VALUE = 2,
    PARSE_BAD_VALUE = 3,
    PARSE_HELP_REQUEST = 4,
    PARSE_DOUBLE_VALUE = 5,
    PARSE_FILE_ERROR = 6,
    PARSE_INTRNAL_ERROR = 7
} parse_return_e;

/* Forward declaration of params_t to avoid circular includes */
typedef struct params params_t;

parse_return_e argument_handler_help(params_t *param, const char *value);
parse_return_e argument_handler_port(params_t *param, const char *value);
parse_return_e argument_handler_address(params_t *param, const char *value);
parse_return_e argument_handler_file(params_t *param, const char *value);
parse_return_e argument_handler_scan(params_t *param, const char *value);
parse_return_e argument_handler_speedup(params_t *param, const char *value);

void address_list_free(addr_node_t **head);

#endif /* ARGUMENT_HANDLERS_H */