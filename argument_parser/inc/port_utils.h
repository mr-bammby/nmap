#ifndef _PORT_UTILS_H_
#define _PORT_UTILS_H_

#include "nmap_types.h"

void init_port_set(port_set_t *set);
short add_port(port_set_t *set, unsigned int value);
void init_port_iterator(port_set_iterator_t *it, const port_set_t *set);
void set_port_iterator_index(port_set_iterator_t *it, int index);
short port_iterator_next(port_set_iterator_t *it, unsigned int *value);


#endif // _PORT_UTILS_H_