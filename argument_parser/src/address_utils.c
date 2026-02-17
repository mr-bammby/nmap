#define _GNU_SOURCE
#include "address_utils.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* historically the validation logic lived in the argument handlers.
   this helper centralizes it so the name is more descriptive. */
int address_is_valid(const char* ip)
{
    if (ip == NULL)
        return 0;

    char buf[20];
    strncpy(buf, ip, sizeof(buf));
    buf[sizeof(buf)-1] = '\0';

    int dots = 0;
    char *ptr;
    char *saveptr;

    ptr = strtok_r(buf, ".", &saveptr);
    while (ptr != NULL) {
        if (!isdigit((unsigned char)*ptr))
            return 0;
        long num = strtol(ptr, NULL, 10);
        if (num < 0 || num > 255)
            return 0;

        ptr = strtok_r(NULL, ".", &saveptr);
        if (ptr != NULL) {
            dots++;
            if (dots > 3)
                return 0;
        }
    }

    return dots == 3;
}

void address_list_free(addr_node_t **head)
{
    while (*head != NULL) {
        addr_node_t *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

int address_list_prepend(addr_node_t** head, const char* ip)
{
    addr_node_t* new_node = malloc(sizeof(addr_node_t));
    if (new_node == NULL)
        return -1;

    strncpy(new_node->addr, ip, sizeof(new_node->addr));
    new_node->addr[sizeof(new_node->addr) - 1] = '\0';
    new_node->next = *head;
    *head = new_node;

    return 0;
}

int parse_address_list(const char* input, addr_node_t **head_p)
{
    addr_node_t *head = *head_p;
    char buffer[256];

    strncpy(buffer, input, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *token;
    char *saveptr;

    token = strtok_r(buffer, ",", &saveptr);
    while (token) {
        if (address_is_valid(token)) {
            if (address_list_prepend(&head, token) != 0) {
                address_list_free(&head);
                return -1;          /* allocation failure */
            }
        } else {
            address_list_free(&head);
            return -1;
        }
        token = strtok_r(NULL, ",", &saveptr);
    }

    *head_p = head;
    return 0;
}
