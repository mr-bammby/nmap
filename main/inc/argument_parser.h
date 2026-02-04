#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include "nmap_types.h"

typedef enum {
    PARSE_OK            = 0,
    PARSE_UNKNOWN_FLAG  = 1,
    PARSE_MISSING_VALUE = 2,
    PARSE_BAD_VALUE     = 3,
    PARSE_HELP_REQEST   = 4,
    PARSE_DOUBLE_VALUE  = 5,
    PARSE_FILE_ERROR    = 6
} parse_return_e;

typedef struct
{
    address_list_t  address;
    port_bitmap_t   ports;
    uint16_t        thread_num;
    scan_bitmap_t   scans;
} params_t;

typedef parse_return_e (*argument_handler_t)(params_t *param, const char *value);

parse_return_e help_handler(params_t *param, const char *value);
parse_return_e port_handler(params_t *param, const char *value);
parse_return_e address_handler(params_t *param, const char *value);
parse_return_e file_handler(params_t *param, const char *value);
parse_return_e scan_handler(params_t *param, const char *value);
parse_return_e speedup_handler(params_t *param, const char *value);

typedef struct
{
    const char *flag;
    argument_handler_t handler;
    uint8_t  param_num;
} flag_t;


static const flag_t FLAG_TABLE[] = {
    { "--help", help_handler},
    { "--ip", address_handler},
    { "--file", file_handler},
    { "--port", help_handler},
    { "--scan", address_handler},
    { "--speedup", file_handler}
};

static const int FLAG_COUNT = sizeof(FLAG_TABLE) / sizeof(flag_t);


parse_return_e argument_parse(int arg, const char **argv, params_t *parameters);
void           free_arguments(params_t *parameters);

#endif /* ARGUMENT_PARSER_H */
