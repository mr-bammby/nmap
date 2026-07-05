#ifndef ADDRESS_UTILS_H
#define ADDRESS_UTILS_H

#include "argument_parser_types.h"
#include "arguments_handlers.h"

/* Internal helper return codes used by lower-level helpers. */
typedef enum
{
    AP_INTERNAL_SUCCESS = 0,
    AP_INTERNAL_ALLOCATION_FAILURE = -1,
    AP_INTERNAL_DNS_FAILURE = -2
} ap_internal_error_e;

typedef enum
{
    AP_BOOL_FALSE = 0,
    AP_BOOL_TRUE = 1
} ap_bool_e;

/* address-related helpers used by multiple argument handlers */

/* verify that the NUL-terminated string is a valid IPv4 dotted-quad;
   returns BOOL_TRUE for valid addresses, BOOL_FALSE otherwise */
ap_bool_e ap_address_is_valid(const char *ip);

/* release all nodes in an address list; the head pointer is set to
   NULL on return */
void ap_address_free_list(argparse_addr_node_t **head);

/* prepend a node containing a copy of `ip` to the list pointed to by
   *head; returns INTERNAL_SUCCESS on success or INTERNAL_FAILURE if malloc
   fails */
ap_internal_error_e ap_address_prepare_list(argparse_addr_node_t **head, const char *ip);

/* parse a comma-separated sequence of IP addresses and append each valid
   address to *head_p.  On success *head_p is updated and the function
   returns ARGPARSE_OK; it returns ARGPARSE_BAD_VALUE for invalid/unresolved
   values, or ARGPARSE_INTERNAL_ERROR on allocation failure. */
argparse_return_e ap_address_parse_list(const char *input, argparse_addr_node_t **head_p);

/* resolve an FQDN to an IPv4 address string; returns AP_INTERNAL_SUCCESS on
   success and fills `ip_buffer` with the resolved IP, or returns
   AP_INTERNAL_FAILURE if resolution fails; `ip_buffer` must be at least
   16 bytes to hold a full IPv4 string plus the null terminator. */
ap_internal_error_e ap_address_resolve_fqdn(const char *fqdn, char *ip_buffer);

#endif /* ADDRESS_UTILS_H */
