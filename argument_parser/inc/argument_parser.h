#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include "argument_parser_types.h"
#include "arguments_handlers.h"

/* Parsed input arguments are stored in this structure. */
typedef struct argparse_params
{
    argparse_addr_node_t *address;
    argparse_port_set_t ports;
    uint16_t thread_num;
    scan_bitmap_t scans;
} argparse_params_t;

/* Type for argument handler functions. */
typedef argparse_return_e (*argparse_argument_handler_t)(argparse_params_t *param, const char *value);

/* Internal flag descriptor */
typedef struct
{
    const char *flag;
    argparse_argument_handler_t handler;
    uint8_t param_num;
} argparse_flag_t;

/* Parse arguments into `parameters`; caller must call `argparse_free_arguments` to free any allocation. */
argparse_return_e argparse_parse_arguments(int arg, const char **argv, argparse_params_t *parameters);

/* Free resources in `parameters` (safe to call with NULL). */
void argparse_free_arguments(argparse_params_t *parameters);

#endif /* ARGUMENT_PARSER_H */
