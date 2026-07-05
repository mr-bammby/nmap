#define _GNU_SOURCE
#define MODULE_DEBUG DEBUG_ADRESS_UTILS
#include "debug.h"
#include "address_utils.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <arpa/inet.h> // Required for inet_ntop
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>


ap_internal_error_e ap_address_resolve_fqdn(const char *fqdn, char *ip_buffer) // buffer needs to be at least 16 bytes
{
    struct addrinfo hints;
    struct addrinfo *info;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;       // Strictly IPv4
    hints.ai_socktype = 0;           // Returns results for all supported protocols (TCP & UDP)

    if (getaddrinfo(fqdn, NULL, &hints, &info) != 0)
        return AP_INTERNAL_DNS_FAILURE;
    if (inet_ntop(info->ai_family, &((struct sockaddr_in *)info->ai_addr)->sin_addr, ip_buffer, 16) == NULL)
    {
        freeaddrinfo(info);
        return AP_INTERNAL_DNS_FAILURE;
    }
    freeaddrinfo(info);
    return AP_INTERNAL_SUCCESS;
}

static ap_bool_e isnum(const char *str)
{
    if (str == NULL || *str == '\0')
        return AP_BOOL_FALSE;

    while (*str)
    {
        if (!isdigit((unsigned char)*str))
            return AP_BOOL_FALSE;
        str++;
    }
    return AP_BOOL_TRUE;
}

/* historically the validation logic lived in the argument handlers.
   this helper centralizes it so the name is more descriptive. */
ap_bool_e ap_address_is_valid(const char *ip)
{
    if (ip == NULL || *ip == '\0')
        return AP_BOOL_FALSE;

    int dots = 0;
    int digits_in_segment = 0;
    int segments = 0;
    const char *p = ip;

    // Reject leading dot
    if (*p == '.')
        return AP_BOOL_FALSE;

    while (*p != '\0')
    {
        if (isdigit((unsigned char)*p))
        {
            // If this is the start of a new segment
            if (digits_in_segment == 0)
                segments++;

            digits_in_segment++;

            // IPv4 segments can't be longer than 3 digits (e.g., 255)
            if (digits_in_segment > 3)
                return AP_BOOL_FALSE;

            // Check value of the segment once we hit a dot or end of string
            if (!isdigit((unsigned char)*(p + 1)))
            {
                char temp[4];
                strncpy(temp, p - (digits_in_segment - 1), digits_in_segment);
                temp[digits_in_segment] = '\0';
                int val = atoi(temp);
                if (val < 0 || val > 255)
                    return AP_BOOL_FALSE;

                // Reject leading zeros like "01" (keep "0" allowed)
                if (digits_in_segment > 1 && temp[0] == '0')
                    return AP_BOOL_FALSE;
            }
        }
        else if (*p == '.')
        {
            dots++;
            // Reject consecutive dots ".." or "..."
            if (*(p + 1) == '.')
                return AP_BOOL_FALSE;
            // Reset digit counter for next segment
            digits_in_segment = 0;
        }
        else
        {
            // Reject any character that isn't a digit or a dot
            return AP_BOOL_FALSE;
        }
        p++;
    }

    // Reject trailing dot (if the last char was '.')
    if (*(p - 1) == '.')
        return AP_BOOL_FALSE;

    // A valid IP must have exactly 3 dots and 4 segments
    return (dots == 3 && segments == 4) ? AP_BOOL_TRUE : AP_BOOL_FALSE;
}

void ap_address_free_list(argparse_addr_node_t **head)
{
    while (*head != NULL)
    {
        argparse_addr_node_t *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

ap_internal_error_e ap_address_prepare_list(argparse_addr_node_t **head, const char *ip)
{
    argparse_addr_node_t *new_node = malloc(sizeof(argparse_addr_node_t));
    if (new_node == NULL)
        return AP_INTERNAL_ALLOCATION_FAILURE;

    strncpy(new_node->addr, ip, sizeof(new_node->addr));
    new_node->addr[sizeof(new_node->addr) - 1] = '\0';
    new_node->next = *head;
    *head = new_node;

    return AP_INTERNAL_SUCCESS;
}

argparse_return_e ap_address_parse_list(const char *input, argparse_addr_node_t **head_p)
{
    argparse_addr_node_t *head = *head_p;
    char buffer[256];
    char fqdn_buffer[16]; // Buffer for resolved IPs from FQDNs, IPv4 max length is 15 + null terminator

    strncpy(buffer, input, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *token;
    char *saveptr;

    token = strtok_r(buffer, ",", &saveptr);
    while (token)
    {
        if (ap_address_is_valid(token) == AP_BOOL_TRUE)
        {
            if (ap_address_prepare_list(&head, token) != AP_INTERNAL_SUCCESS)
            {
                ap_address_free_list(&head);
                return ARGPARSE_INTERNAL_ERROR;
            }
        }
        else if (ap_address_resolve_fqdn(token, fqdn_buffer) == AP_INTERNAL_SUCCESS)
        {
            LOGD("Resolved FQDN '%s' to IP '%s'\n", token, fqdn_buffer);
            if (ap_address_prepare_list(&head, fqdn_buffer) != AP_INTERNAL_SUCCESS)
            {
                ap_address_free_list(&head);
                return ARGPARSE_INTERNAL_ERROR;
            }
        }
        else
        {
            ap_address_free_list(&head);
            return ARGPARSE_BAD_VALUE;
        }
        token = strtok_r(NULL, ",", &saveptr);
    }

    *head_p = head;
    return ARGPARSE_OK;
}
