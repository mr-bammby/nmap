#ifndef ARGUMENT_PARSER_PORT_H
#define ARGUMENT_PARSER_PORT_H

#include "argument_parser_types.h"

void argparse_port_init_set(argparse_port_set_t *set);
short argparse_port_add(argparse_port_set_t *set, unsigned int value);
short argparse_port_get(const argparse_port_set_t *set, int index, unsigned int *value);
short argparse_port_find(const argparse_port_set_t *set, unsigned int target, int *index);
void argparse_port_iterator_init(argparse_port_set_iterator_t *it, const argparse_port_set_t *set);
void argparse_port_iterator_set_index(argparse_port_set_iterator_t *it, int index);
short argparse_port_iterator_next(argparse_port_set_iterator_t *it, unsigned int *value);
int argparse_port_set_get_size(const argparse_port_set_t *set);


#endif // ARGUMENT_PARSER_PORT_H