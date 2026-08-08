#define MODULE_DEBUG DEBUG_ARGUMENT_HANDLER_PORTS
#include "debug.h"
#include "argument_parser.h"
#include "argument_parser_port.h"
#include "argument_parser_types.h"
#include <string.h>
#include <ctype.h>


typedef enum
{
    START,
    NUMBER,
    SPAN,
    SECOND_NUMBER
} state_t;

/* set the bit corresponding to `idx` in the supplied port bitmap */
static inline short port_bitmap_set(argparse_port_set_t *set, uint16_t idx)
{
    if (set != NULL)
    {
        return argparse_port_add(set, idx);
    }
    return 0;
}

/* parse a comma-separated list of port numbers and ranges into a
   bitmap; returns PARSE_OK on success, PARSE_BAD_VALUE on invalid input,
   or PARSE_INTERNAL_ERROR on internal failures such as overflow */
static argparse_return_e parse_port_range_set(const char *input, argparse_port_set_t *set)
{
    state_t st = START;
    uint32_t num = 0;
    int32_t start = -1;
    int32_t end = -1;
    uint32_t start_idx = 0;
    uint32_t idx = 0;

    const char *p = input;

    argparse_port_init_set(set);

    while (1)
    {
        char c = *p;

        switch (st)
        {
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
                return ARGPARSE_OK;
            }
            else
            {
                return ARGPARSE_BAD_VALUE; /* error */
            }
            break;

        /* --------------------------------------------- */
        case NUMBER:
            if (idx > (start_idx + 6))
            {
                return ARGPARSE_BAD_VALUE;
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
                if (num < 1 || num > PORT_MAX_PORT)
                    return ARGPARSE_BAD_VALUE;
                if (port_bitmap_set(set, num) != 0)
                    return ARGPARSE_INTERNAL_ERROR;

                st = START;

                if (c == '\0')
                    return ARGPARSE_OK;
            }
            else
            {
                return ARGPARSE_BAD_VALUE; /* invalid char */
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
                return ARGPARSE_BAD_VALUE;
            }
            break;

        /* --------------------------------------------- */
        case SECOND_NUMBER:
            if (idx > (start_idx + 6))
            {
                return ARGPARSE_BAD_VALUE;
            }
            if (isdigit(c))
            {
                num = num * 10 + (c - '0');
            }
            else if (c == ',' || c == '\0')
            {
                end = num;

                if (start < 1 || end > PORT_MAX_PORT || start > end)
                {
                    return ARGPARSE_BAD_VALUE;
                }

                for (int v = start; v <= end; v++)
                {
                    if (port_bitmap_set(set, v) != 0)
                        return ARGPARSE_INTERNAL_ERROR;
                }

                st = START;

                if (c == '\0')
                {
                    return ARGPARSE_OK;
                }
            }
            else
            {
                return ARGPARSE_BAD_VALUE;
            }
            break;
        }
        if (c == '\0')
        {
            return ARGPARSE_OK;
        }
        idx++;
        p++;
    }
    return ARGPARSE_OK;
}

argparse_return_e ap_handler_port(argparse_params_t *param, const char *value)
{
    if (param->ports.count != 0)
    {
        return ARGPARSE_DOUBLE_VALUE;
    }

    return parse_port_range_set(value, &(param->ports));
}