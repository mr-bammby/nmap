#include <string.h>

#include "argument_parser.h"


static inline void bitset_set(port_bitmap_t *bitset, uint16_t idx)
{
    bits[idx / BITMAP_BYTE_SIZE] |= 1u << (idx % BITMAP_BYTE_SIZE);
}

typedef enum
{
    START,
    NUMBER,
    SPAN,
    SECOND_NUMBER
} state_t;

static int parse_range_bitmap(const char *s, port_bitmap_t *bits) {
    memset(bits, 0, sizeof(port_bitmap_t));

    state_t st = START;
    uint16_t num = 0;
    int32_t start = -1;
    int32_t end = -1;
    uint32_t start_idx = 0;
    uint32_t idx = 0;

    const char *p = s;

    while (*p != '\0')
    {
        char c = *p;

        switch (st) {
        /* --------------------------------------------- */
        case START:
            if (isdigit(c))
            {
                num = c - '0';
                st = NUMBER;
                start_idx = idx;
            }
            else if (c == ',')
            {
                /* skip separators */
            }
            else if (c == '\0')
            {
                return 0;
            }
            else
            {
                return -1; /* error */
            }
            break;

        /* --------------------------------------------- */
        case NUMBER:
            if (idx > (start_idx + 4))
            {
                return -7;
            }
            if (isdigit(c))
            {
                num = (num * 10) + (c - '0');
            } 
            else if (c == '-')
            {
                start = num;
                st = SPAN;
            }
            else if (c == ',' || c == '\0')
            {
                if (num < 1 || num > MAX_BITS)
                    return -2;

                bitset_set(bits, num);

                st = START;

                if (c == '\0')
                    return 0;
            }
            else {
                return -3; /* invalid char */
            }
            break;

        /* --------------------------------------------- */
        case SPAN:
            if (isdigit(c))
            {
                num = c - '0';
                st = SECOND_NUMBER;
                start_idx = idx;
            }
            else
            {
                return -4;
            }
            break;

        /* --------------------------------------------- */
        case SECOND_NUMBER:
            if (idx > (start_idx + 4))
            {
                return -7;
            }
            if (isdigit(c))
            {
                num = num * 10 + (c - '0');
            }
            else if (c == ',' || c == '\0')
            {
                end = num;

                if (start < 1 || end > NUMBER_OF_PORTS || start > end)
                {
                    return -5;
                }

                for (int v = start; v <= end; v++)
                {
                    bitset_set(bits, v);
                }

                st = START;

                if (c == '\0')
                {
                    return 0;
                }
            }
            else
            {
                return -6;
            }
            break;
        }
        idx++;
        p++;
    }
    return (0);
}


parse_return_e help_handler(params_t *param, const char *value)
{
    return PARSE_HELP_REQEST;
}

parse_return_e port_handler(params_t *param, const char *value)
{
    for (uint8_t i = 0; i < BITMAP_BYTE_SIZE; i++)
    {
        if (param->ports[i] != 0u)
        {
            return (PARSE_DOUBLE_VALUE);
        }
    }
    if (parse_range_bitmap(value, &(param->ports)) == 0)
    {
        return (PARSE_BAD_VALUE)
    }
    return (PARSE_OK);
}


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

    strncpy(new_node->ip, ip, 16);
    new_node->ip[15] = '\0';
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
            return(-1)
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
    if (parse_ip_list(value, &(param.address)) != 0)
    {
        return (PARSE_BAD_VALUE);
    }
    return (PARSE_OK)
}

parse_return_e file_handler(params_t *param, const char *value);

#define MAX_TOKENS 6

// Constant array of allowed keywords
static const char* const validTokens[MAX_TOKENS] = {
    "SYN",
    "NULL",
    "FIN",
    "XMAS",
    "UDP"
};

uint8_t parse_tokens_to_bitmap(const char* input, scan_bitmap_t *bitmap)
{
    if (!input)
        return 0;

    char buffer[128];

    // Copy input so strtok doesn't modify original
    strncpy(buffer, input, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = strtok(buffer, ",");

    while (token != NULL)
    {
        // Compare with valid tokens
        int i;
        for (i = 0; i < MAX_TOKENS; i++)
        {
            if (strcmp(token, validTokens[i]) == 0)
            {
                *bitmap |= (1 << i);   // set bit
                break;
            }
        }
        if (i == MAX_TOKENS)
        {
            return (-1);
        }
        token = strtok(NULL, ",");
    }

    return 0;
}

parse_return_e scan_handler(params_t *param, const char *value)
{
    if (param->scans != 0)
        return (PARSE_DOUBLE_VALUE);
    if (parse_tokens_to_bitmap(value, &(param->scans)) != 0)
    {
        return (PARSE_BAD_VALUE);
    }
    return (PARSE_OK);
}

parse_return_e speedup_handler(params_t *param, const char *value)
{
    if (param->thread_num != 0)
        return (PARSE_DOUBLE_VALUE);
    if (isdigit(value) == 0)
        return (PARSE_BAD_VALUE);
    param->thread_num = atoi(value);

    return (PARSE_OK);
}
