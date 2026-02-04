#include "argument_parser.h"

/* Check if one IPv4 address is valid */
int is_valid_ip(const char* ip)
{
    int num, dots = 0;
    char *ptr, buf[20];

    if (ip == NULL)
        return 0;

    strncpy(buf, ip, sizeof(buf));
    buf[sizeof(buf)-1] = '\0';

    ptr = strtok(buf, ".");
    while (ptr != NULL)
    {
        if (!isdigit(*ptr))
            return 0;
        num = atoi(ptr);
        if (num < 0 || num > 255)
            return 0;

        ptr = strtok(NULL, ".");
        if (ptr != NULL)
        {
            dots++;
            if (dots > 3)
                return 0;
        }
    }

    return dots == 3;
}

void ll_free(addr_node_t* head)
{
    while (head == NULL)
    {
        free(head->addr);
        free(head);
        head = head->next;
    }
}

/* Append new node to linked list */
int ll_append(addr_node_t** head, const char* ip)
{
    addr_node_t* new_node = malloc(sizeof(addr_node_t));

    if (new_node == NULL)
        return -1;

    strncpy(new_node->addr, ip, 16);
    new_node->addr[15] = '\0';
    new_node->next = *head;
    *head = new_node;

    return 0;
}

/* Parse a list like "1.2.3.4,5.6.7.8" and store into linked list */
int parse_ip_list(const char* input, addr_node_t **head_p)
{
    addr_node_t* head = *head_p;
    char buffer[256];

    strncpy(buffer, input, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = strtok(buffer, ",");
    while (token)
    {
        if (is_valid_ip(token))
        {
            ll_append(&head, token);
        }
        else
        {
            ll_free(head);
            return(-1);
        }
        token = strtok(NULL, ",");
    }

    return 0;
}

parse_return_e address_handler(params_t *param, const char *value)
{
    if (param->address != NULL)
    {
        return (PARSE_DOUBLE_VALUE);
    }
    if (parse_ip_list(value, &(param->address)) != 0)
    {
        return (PARSE_BAD_VALUE);
    }
    return (PARSE_OK);
}
