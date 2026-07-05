#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include "argument_parser_types.h"
#include "arguments_handlers.h"

typedef struct argparse_params
{
    argparse_addr_node_t *address;
    argparse_port_set_t ports;
    uint16_t thread_num;
    scan_bitmap_t scans;
} argparse_params_t;

typedef argparse_return_e (*argparse_argument_handler_t)(argparse_params_t *param, const char *value);

typedef struct
{
    const char *flag;
    argparse_argument_handler_t handler;
    uint8_t param_num;
} argparse_flag_t;

static const argparse_flag_t FLAG_TABLE[] = {
    {"--help", ap_handler_help, 0},
    {"--ip", ap_handler_address, 1},
    {"--file", ap_handler_file, 1},
    {"--port", ap_handler_port, 1},
    {"--scan", ap_handler_scan, 1},
    {"--speedup", ap_handler_speedup, 1}};

#define FLAG_COUNT (sizeof(FLAG_TABLE) / sizeof(argparse_flag_t))

argparse_return_e argparse_parse_arguments(int arg, const char **argv, argparse_params_t *parameters);
void argparse_free_arguments(argparse_params_t *parameters);

#endif /* ARGUMENT_PARSER_H */
