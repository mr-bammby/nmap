#ifndef ARGUMENT_PARSER_PORT_H
#define ARGUMENT_PARSER_PORT_H

#include "argument_parser_types.h"

/* Initialize `set` to an empty port set. */
void argparse_port_init_set(argparse_port_set_t *set);

/* Add `value` to `set` (keeps data sorted and unique). */
short argparse_port_add(argparse_port_set_t *set, unsigned int value);

/* Retrieve the port at `index` into `value`. Returns 0 on success. */
short argparse_port_get(const argparse_port_set_t *set, int index, unsigned int *value);

/* Find `target` in `set`; on success store index and return 0. */
short argparse_port_find(const argparse_port_set_t *set, unsigned int target, int *index);

/* Initialize iterator `it` to traverse `set`. */
void argparse_port_iterator_init(argparse_port_set_iterator_t *it, const argparse_port_set_t *set);

/* Set iterator `it` to `index` (no-op if out of bounds). */
void argparse_port_iterator_set_index(argparse_port_set_iterator_t *it, int index);

/* Advance iterator `it` and store next value in `value`. Returns 0 on success. */
short argparse_port_iterator_next(argparse_port_set_iterator_t *it, unsigned int *value);

/* Return number of ports stored in `set` (0 if `set` is NULL). */
int argparse_port_set_get_size(const argparse_port_set_t *set);


#endif // ARGUMENT_PARSER_PORT_H