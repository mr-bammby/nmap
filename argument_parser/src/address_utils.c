#define _GNU_SOURCE
#include "address_utils.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

uint8_t isnum(const char *str)
{
    if (str == NULL || *str == '\0')
        return 0;

    while (*str)
    {
        if (!isdigit((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

/* historically the validation logic lived in the argument handlers.
   this helper centralizes it so the name is more descriptive. */
int address_is_valid(const char *ip)
{
    if (ip == NULL || *ip == '\0')
        return 0;

    int dots = 0;
    int digits_in_segment = 0;
    int segments = 0;
    const char *p = ip;

    // Reject leading dot
    if (*p == '.')
        return 0;

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
                return 0;

            // Check value of the segment once we hit a dot or end of string
            if (!isdigit((unsigned char)*(p + 1)))
            {
                char temp[4];
                strncpy(temp, p - (digits_in_segment - 1), digits_in_segment);
                temp[digits_in_segment] = '\0';
                int val = atoi(temp);
                if (val < 0 || val > 255)
                    return 0;

                // Reject leading zeros like "01" (keep "0" allowed)
                if (digits_in_segment > 1 && temp[0] == '0')
                    return 0;
            }
        }
        else if (*p == '.')
        {
            dots++;
            // Reject consecutive dots ".." or "..."
            if (*(p + 1) == '.')
                return 0;
            // Reset digit counter for next segment
            digits_in_segment = 0;
        }
        else
        {
            // Reject any character that isn't a digit or a dot
            return 0;
        }
        p++;
    }

    // Reject trailing dot (if the last char was '.')
    if (*(p - 1) == '.')
        return 0;

    // A valid IP must have exactly 3 dots and 4 segments
    return (dots == 3 && segments == 4);
}

void address_list_free(addr_node_t **head)
{
    while (*head != NULL)
    {
        addr_node_t *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

int address_list_prepend(addr_node_t **head, const char *ip)
{
    addr_node_t *new_node = malloc(sizeof(addr_node_t));
    if (new_node == NULL)
        return -1;

    strncpy(new_node->addr, ip, sizeof(new_node->addr));
    new_node->addr[sizeof(new_node->addr) - 1] = '\0';
    new_node->next = *head;
    *head = new_node;

    return 0;
}

int parse_address_list(const char *input, addr_node_t **head_p)
{
    addr_node_t *head = *head_p;
    char buffer[256];

    strncpy(buffer, input, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *token;
    char *saveptr;

    token = strtok_r(buffer, ",", &saveptr);
    while (token)
    {
        if (address_is_valid(token))
        {
            if (address_list_prepend(&head, token) != 0)
            {
                address_list_free(&head);
                return -1; /* allocation failure */
            }
        }
        else
        {
            address_list_free(&head);
            return -1;
        }
        token = strtok_r(NULL, ",", &saveptr);
    }

    *head_p = head;
    return 0;
}
