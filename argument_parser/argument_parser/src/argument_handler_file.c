#define _GNU_SOURCE
#include "argument_parser.h"
#include "address_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

parse_return_e argument_handler_file(params_t *param, const char *value)
{
    if (param->address != NULL)
        return PARSE_DOUBLE_VALUE;

    FILE *file = fopen(value, "r");
    if (!file)
        return PARSE_FILE_ERROR;

    addr_node_t *head = NULL;
    char line[32];

    while (fgets(line, sizeof(line), file))
    {
        /* Remove newline and trim whitespace */
        char *addr;
        char *saveptr2;

        addr = strtok_r(line, "\r\n", &saveptr2);
        if (!addr)
        {
            address_list_free(&head);
            fclose(file);
            return PARSE_BAD_VALUE;
        }

        if (address_is_valid(addr))
        {
            if (address_list_prepend(&head, addr) != 0)
            {
                address_list_free(&head);
                fclose(file);
                return PARSE_INTRNAL_ERROR;
            }
        }
        else
        {
            address_list_free(&head);
            fclose(file);
            return PARSE_BAD_VALUE;
        }
    }

    fclose(file);
    param->address = head;
    return PARSE_OK;
}
