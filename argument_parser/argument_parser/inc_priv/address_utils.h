#ifndef ADDRESS_UTILS_H
#define ADDRESS_UTILS_H

#include "nmap_types.h"  /* for addr_node_t */

/* address‑related helpers used by multiple argument handlers */

/* verify that the NUL‑terminated string is a valid IPv4
   dotted‑quad ("x.x.x.x"); returns 1 for valid, 0 otherwise */
int address_is_valid(const char *ip);

/* release all nodes in an address list; the head pointer is set to
   NULL on return */
void address_list_free(addr_node_t **head);

/* prepend a node containing a copy of `ip` to the list pointed to by
   *head; returns 0 on success or -1 if malloc fails */
int address_list_prepend(addr_node_t **head, const char *ip);

/* parse a comma‑separated sequence of IP addresses and append each valid
   address to *head_p.  On success *head_p is updated and the function
   returns 0; it returns -1 if any address is invalid or on allocation
   failure. */
int parse_address_list(const char *input, addr_node_t **head_p);

#endif /* ADDRESS_UTILS_H */
