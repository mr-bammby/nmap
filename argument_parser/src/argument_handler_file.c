#define _GNU_SOURCE
#define MODULE_DEBUG DEBUG_ARGUMENT_HANDLER_FILE
#include "debug.h"
#include "argument_parser.h"
#include "address_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


argparse_return_e ap_handler_file(argparse_params_t *param, const char *value)
{
    if (param->address != NULL)
        return ARGPARSE_DOUBLE_VALUE;

    FILE *file = fopen(value, "r");
    if (!file)
        return ARGPARSE_FILE_ERROR;

    argparse_addr_node_t *head = NULL;
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
            ap_address_free_list(&head);
            fclose(file);
            return ARGPARSE_BAD_VALUE;
        }

        while (isspace((unsigned char)*addr))
            addr++;

        end = addr + strlen(addr) - 1;
        while (end >= addr && isspace((unsigned char)*end))
            *end-- = '\0';

        if (*addr == '\0')
        {
            free(line);
            ap_address_free_list(&head);
            fclose(file);
            return ARGPARSE_BAD_VALUE;
        }

        if (ap_address_is_valid(addr) == AP_BOOL_TRUE)
        {
            if (ap_address_prepare_list(&head, addr) != AP_INTERNAL_SUCCESS)
            {
                free(line);
                ap_address_free_list(&head);
                fclose(file);
                return ARGPARSE_INTERNAL_ERROR;
            }
        }
        else if (ap_address_resolve_fqdn(addr, fqdn_buffer) == AP_INTERNAL_SUCCESS)
        {
            if (ap_address_prepare_list(&head, fqdn_buffer) != AP_INTERNAL_SUCCESS)
            {
                free(line);
                ap_address_free_list(&head);
                fclose(file);
                return ARGPARSE_INTERNAL_ERROR;
            }
        }
        else
        {
            free(line);
            ap_address_free_list(&head);
            fclose(file);
            return ARGPARSE_BAD_VALUE;
        }
    }

    free(line);

    if (ferror(file))
    {
        ap_address_free_list(&head);
        fclose(file);
        return ARGPARSE_FILE_ERROR;
    }

    fclose(file);
    param->address = head;
    return ARGPARSE_OK;
}
