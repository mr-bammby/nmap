#ifndef ADDRESS_UTILS_H
#define ADDRESS_UTILS_H

#include "nmap_types.h"  /* for addr_node_t */
#include "arguments_handlers.h"

/* Internal helper return codes used by lower-level helpers. */
typedef enum
{
    INTERNAL_SUCCESS = 0,
    INTERNAL_ALLOCATION_FAILURE = -1,
    INTERNAL_DNS_FAILURE = -2
} internal_error_e;

typedef enum
{
    BOOL_FALSE = 0,
    BOOL_TRUE = 1
} bool_e;

/* address-related helpers used by multiple argument handlers */

/* verify that the NUL-terminated string is a valid IPv4 dotted-quad;
   returns BOOL_TRUE for valid addresses, BOOL_FALSE otherwise */
bool_e address_is_valid(const char *ip);

/* release all nodes in an address list; the head pointer is set to
   NULL on return */
void address_list_free(addr_node_t **head);

/* prepend a node containing a copy of `ip` to the list pointed to by
   *head; returns INTERNAL_SUCCESS on success or INTERNAL_FAILURE if malloc
   fails */
internal_error_e address_list_prepend(addr_node_t **head, const char *ip);

/* parse a comma-separated sequence of IP addresses and append each valid
   address to *head_p.  On success *head_p is updated and the function
   returns PARSE_OK; it returns PARSE_BAD_VALUE for invalid/unresolved
   values, or PARSE_INTERNAL_ERROR on allocation failure. */
parse_return_e parse_address_list(const char *input, addr_node_t **head_p);

/* resolve an FQDN to an IPv4 address string; returns INTERNAL_SUCCESS on
   success and fills `ip_buffer` with the resolved IP, or returns
   INTERNAL_FAILURE if resolution fails; `ip_buffer` must be at least
   16 bytes to hold a full IPv4 string plus the null terminator. */
internal_error_e fqdn_resolve(const char *fqdn, char *ip_buffer);


#endif /* ADDRESS_UTILS_H */
