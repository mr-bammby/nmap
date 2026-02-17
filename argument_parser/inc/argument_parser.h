#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include "nmap_types.h"
#include "arguments_handlers.h"

typedef struct params
{
    address_list_t address;
    port_bitmap_t ports;
    uint16_t thread_num;
    scan_bitmap_t scans;
} params_t;

typedef parse_return_e (*argument_handler_t)(params_t *param, const char *value);

typedef struct
{
    const char *flag;
    argument_handler_t handler;
    uint8_t param_num;
} flag_t;

static const flag_t FLAG_TABLE[] = {
    {"--help", argument_handler_help, 0},
    {"--ip", argument_handler_address, 1},
    {"--file", argument_handler_file, 1},
    {"--port", argument_handler_port, 1},
    {"--scan", argument_handler_scan, 1},
    {"--speedup", argument_handler_speedup, 1}};

#define FLAG_COUNT (sizeof(FLAG_TABLE) / sizeof(flag_t))

parse_return_e argument_parse(int arg, const char **argv, params_t *parameters);
void free_arguments(params_t *parameters);

#endif /* ARGUMENT_PARSER_H */
