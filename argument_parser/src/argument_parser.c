#define MODULE_DEBUG DEBUG_ARGUMENT_PARSER
#include "debug.h"
#include <string.h>
#include "argument_parser.h"
#include "nmap_types.h"
#include "port_utils.h"


#define DEFAULT_PORTS_STR "1-1024"
#define DEFAULT_THREAD_NUM 1
#define DEFAULT_SCANS 0x3f


parse_return_e argument_parse(int arg, const char **argv, params_t *parameters)
{
    int i = 1;

    if (parameters == NULL)
    {
        return PARSE_INTERNAL_ERROR;
    }

    memset(parameters, 0, sizeof(*parameters));
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
        parameters->thread_num = DEFAULT_THREAD_NUM;
    }
    if (parameters->scans == 0)
    {
        parameters->scans = DEFAULT_SCANS;
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
