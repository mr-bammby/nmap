#ifndef ARGUMENT_HANDLERS_H
#define ARGUMENT_HANDLERS_H

#include "argument_parser_types.h"



/* Forward declaration of params_t to avoid circular includes */
typedef struct argparse_params argparse_params_t;

argparse_return_e ap_handler_help(argparse_params_t *param, const char *value);
argparse_return_e ap_handler_port(argparse_params_t *param, const char *value);
argparse_return_e ap_handler_address(argparse_params_t *param, const char *value);
argparse_return_e ap_handler_file(argparse_params_t *param, const char *value);
argparse_return_e ap_handler_scan(argparse_params_t *param, const char *value);
argparse_return_e ap_handler_speedup(argparse_params_t *param, const char *value);

void ap_address_free_list(argparse_addr_node_t **head);

#endif /* ARGUMENT_HANDLERS_H */