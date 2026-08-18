#define MODULE_DEBUG DEBUG_ARGUMENT_PARSER
#include "debug.h"
#include <string.h>
#include "argument_parser.h"
#include "argument_parser_types.h"
#include "argument_parser_port.h"


#define DEFAULT_PORTS_STR "1-1024"
#define DEFAULT_THREAD_NUM 1
#define DEFAULT_SCANS 0x3f

static const argparse_flag_t FLAG_TABLE[] = {
    {"--help", ap_handler_help, 0},
    {"--ip", ap_handler_address, 1},
    {"--file", ap_handler_file, 1},
    {"--port", ap_handler_port, 1},
    {"--scan", ap_handler_scan, 1},
    {"--speedup", ap_handler_speedup, 1}};

#define FLAG_COUNT (sizeof(FLAG_TABLE) / sizeof(argparse_flag_t))


argparse_return_e argparse_parse_arguments(int arg, const char **argv, argparse_params_t *parameters)
{
    int i = 1;

    if (parameters == NULL)
    {
        return ARGPARSE_INTERNAL_ERROR;
    }

    memset(parameters, 0, sizeof(*parameters));
    argparse_port_init_set(&parameters->ports);

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
                            ap_address_free_list(&parameters->address);
                        }
                        return ARGPARSE_MISSING_VALUE;
                    }
                    value = argv[i + 1];
                }
                argparse_return_e res = FLAG_TABLE[j].handler(parameters, value);
                if (res != ARGPARSE_OK)
                {
                    if (parameters->address != NULL)
                    {
                        ap_address_free_list(&parameters->address);
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
                ap_address_free_list(&parameters->address);
            }
            return ARGPARSE_UNKNOWN_FLAG;
        }
        i++;
    }

    if (parameters->address == NULL)
    {
        return ARGPARSE_MISSING_VALUE; /* at least one address is required */
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
        argparse_return_e res = ap_handler_port(parameters, DEFAULT_PORTS_STR);
        if (res != ARGPARSE_OK)
        {
            return res;
        }
    }

    return ARGPARSE_OK;
}

void argparse_free_arguments(argparse_params_t *parameters)
{
    if (parameters == NULL)
        return;

    if (parameters->address != NULL)
    {
        ap_address_free_list(&parameters->address);
        parameters->address = NULL;
    }

    /* clear other fields */
    parameters->ports.count = 0;
    parameters->thread_num = 0;
    parameters->scans = 0;
}
