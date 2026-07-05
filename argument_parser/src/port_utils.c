#define MODULE_DEBUG DEBUG_PORT_UTILS
#include "debug.h"
#include "argument_parser_types.h"
#include <stdio.h>


// --- Set Functions ---

void argparse_port_init_set(argparse_port_set_t *set)
{
    set->count = 0;
}

short argparse_port_add(argparse_port_set_t *set, unsigned int value)
{
    for (int i = 0; i < set->count; i++)
    {
        if (set->data[i] == value)
            return 0; // Ignore duplicate
    }

    if (set->count >= PORT_NUMBER_OF_PORTS)
    {
        LOGE("Error: Set overflow.\n");
        return -1;
    }

    if (set->count == 0 || set->data[set->count - 1] < value)
    {
        set->data[set->count++] = value;
        return 0;
    }
    
    for (int i = 0; i < set->count; i++)
    {
        if (set->data[i] > value)
        {
            for (int j = set->count; j > i; j--)
            {
                set->data[j] = set->data[j - 1];
            }
            set->data[i] = value;
            set->count++;
            return 0; // Success
        }
    }
    set->data[set->count++] = value; // Add at the end
    return 0;
}

// --- Iterator Functions ---

// Initializes the iterator and links it to a set
void argparse_port_iterator_init(argparse_port_set_iterator_t *it, const argparse_port_set_t *set)
{
    it->set = set;
    it->index = 0;
}

// Manual control over the iterator position
void argparse_port_iterator_set_index(argparse_port_set_iterator_t *it, int index)
{
    if (index >= 0 && index < it->set->count)
    {
        it->index = index;
    }
    else
    {
        LOGW("Iterator index out of bounds.\n");
    }
}

// Fetches the current value and moves the pointer forward
short argparse_port_iterator_next(argparse_port_set_iterator_t *it, unsigned int *out_value)
{
    if (it->index < it->set->count)
    {
        *out_value = it->set->data[it->index++];
        return 0; // Success
    }
    return -1; // Failure
}

int argparse_port_set_get_size(const argparse_port_set_t *set)
{
    return set->count;
}

