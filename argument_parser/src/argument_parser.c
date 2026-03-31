#include <string.h>
#include "argument_parser.h"
#include "nmap_types.h"
#include "port_utils.h"

static const params_t DEFAULT_PARAMS = {
    .address = NULL,                                    /* no addresses by default, user must specify at least one */
    .ports = {0}, /* all ports enabled by default */
    .thread_num = 1,                                    /* one thread by default */
    .scans = 0x3f                                       /* all scan types enabled by default */
};

#define DEFAULT_PORTS_STR "1-1024"


parse_return_e argument_parse(int arg, const char **argv, params_t *parameters)
{
    int i = 1;

    init_port_set(&parameters->ports);

    while (i < arg)
    {
        int found = 0;
        for (size_t j = 0; j < FLAG_COUNT; ++j)
        {
            if (strcmp(argv[i], FLAG_TABLE[j].flag) == 0)
            {
                found = 1;
                const char *value = NULL;
                if (FLAG_TABLE[j].param_num > 0)
                {
                    if (i + 1 >= arg)
                    {
                        if (parameters->address != NULL)
                        {
                            address_list_free(&parameters->address);
                        }
                        return PARSE_MISSING_VALUE;
                    }
                    value = argv[i + 1];
                }
                parse_return_e res = FLAG_TABLE[j].handler(parameters, value);
                if (res != PARSE_OK)
                {
                    if (parameters->address != NULL)
                    {
                        address_list_free(&parameters->address);
                    }
                    return res;
                }
                i += FLAG_TABLE[j].param_num;
                break;
            }
        }
        if (!found)
        {
            if (parameters->address != NULL)
            {
                address_list_free(&parameters->address);
            }
            return PARSE_UNKNOWN_FLAG;
        }
        i++;
    }

    if (parameters->address == NULL)
    {
        return PARSE_MISSING_VALUE; /* at least one address is required */
    }
    if (parameters->thread_num == 0)
    {
        parameters->thread_num = DEFAULT_PARAMS.thread_num;
    }
    if (parameters->scans == 0)
    {
        parameters->scans = DEFAULT_PARAMS.scans;
    }
    if (parameters->ports.count == 0)
    {
        parse_return_e res = argument_handler_port(parameters, DEFAULT_PORTS_STR);
        if (res != PARSE_OK)
        {
            return res;
        }
    }

    return PARSE_OK;
}

void free_arguments(params_t *parameters)
{
    if (parameters == NULL)
        return;

    if (parameters->address != NULL)
    {
        address_list_free(&parameters->address);
    }

    /* clear other fields */
    parameters->ports.count = 0;
    parameters->thread_num = 0;
    parameters->scans = 0;
}
