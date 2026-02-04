#include "argument_parser.h"

typedef enum
{
    START,
    NUMBER,
    SPAN,
    SECOND_NUMBER
} state_t;

static inline void bitset_set(port_bitmap_t bitset, uint16_t idx)
{
	if (bitset != NULL)
		bitset[idx / BITMAP_BYTE_SIZE] |= 1u << (idx % BITMAP_BYTE_SIZE);
}

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
                if (num < 1 || num > NUMBER_OF_PORTS)
                    return -2;

                bitset_set(*bits, num);

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
                    bitset_set(*bits, v);
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
        return (PARSE_BAD_VALUE);
    }
    return (PARSE_OK);
}