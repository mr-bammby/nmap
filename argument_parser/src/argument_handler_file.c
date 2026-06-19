#define _GNU_SOURCE
#include "argument_parser.h"
#include "address_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "debug.h"

parse_return_e argument_handler_file(params_t *param, const char *value)
{
    if (param->address != NULL)
        return PARSE_DOUBLE_VALUE;

    FILE *file = fopen(value, "r");
    if (!file)
        return PARSE_FILE_ERROR;

    addr_node_t *head = NULL;
    char *line = NULL;
    size_t line_size = 0;
    char fqdn_buffer[16]; // Buffer for resolved IPs from FQDNs, IPv4 max length is 15 + null terminator

    while (getline(&line, &line_size, file) != -1)
    {
        char *addr;
        char *saveptr2;
        char *end;

        addr = strtok_r(line, "\r\n", &saveptr2);
        if (!addr)
        {
            free(line);
            address_list_free(&head);
            fclose(file);
            return PARSE_BAD_VALUE;
        }

        while (isspace((unsigned char)*addr))
            addr++;

        end = addr + strlen(addr) - 1;
        while (end >= addr && isspace((unsigned char)*end))
            *end-- = '\0';

        if (*addr == '\0')
        {
            free(line);
            address_list_free(&head);
            fclose(file);
            return PARSE_BAD_VALUE;
        }

        if (address_is_valid(addr) == BOOL_TRUE)
        {
            if (address_list_prepend(&head, addr) != INTERNAL_SUCCESS)
            {
                free(line);
                address_list_free(&head);
                fclose(file);
                return PARSE_INTERNAL_ERROR;
            }
        }
        else if (fqdn_resolve(addr, fqdn_buffer) == INTERNAL_SUCCESS)
        {
            if (address_list_prepend(&head, fqdn_buffer) != INTERNAL_SUCCESS)
            {
                free(line);
                address_list_free(&head);
                fclose(file);
                return PARSE_INTERNAL_ERROR;
            }
        }
        else
        {
            free(line);
            address_list_free(&head);
            fclose(file);
            return PARSE_BAD_VALUE;
        }
    }

    free(line);

    if (ferror(file))
    {
        address_list_free(&head);
        fclose(file);
        return PARSE_FILE_ERROR;
    }

    fclose(file);
    param->address = head;
    return PARSE_OK;
}
