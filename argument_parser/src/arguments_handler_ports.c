#include "argument_parser.h"
#include "nmap_types.h"
#include "port_utils.h"
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
static inline void port_bitmap_set(port_set_t *set, uint16_t idx)
{
    if (set != NULL)
    {
        add_port(set,idx);
    }
}

/* parse a comma‑separated list of port numbers and ranges into a
   bitmap; returns 0 on success, negative codes on error */
static int parse_port_range_set(const char *input, port_set_t *set)
{
    state_t st = START;
    uint16_t num = 0;
    int32_t start = -1;
    int32_t end = -1;
    uint32_t start_idx = 0;
    uint32_t idx = 0;

    const char *p = input;

    init_port_set(set);

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
                if (num < 1 || num > NUMBER_OF_PORTS)
                    return -2;
                port_bitmap_set(set, num);

                st = START;

                if (c == '\0')
                    return 0;
            }
            else
            {
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
                    port_bitmap_set(set, v);
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
        if (c == '\0')
        {
            return 0;
        }
        idx++;
        p++;
    }
    return (0);
}

parse_return_e argument_handler_port(params_t *param, const char *value)
{
    static int reenter = 0;
    if (reenter)
    {
        return (PARSE_DOUBLE_VALUE);
    }
    reenter = 1;
    if (parse_port_range_set(value, &(param->ports)) != 0)
    {
        return (PARSE_BAD_VALUE);
    }
    return (PARSE_OK);
}