#include "nmap_types.h"
#include <stdio.h>

// --- Set Functions ---

void init_port_set(port_set_t *set)
{
    set->count = 0;
}

short add_port(port_set_t *set, unsigned int value)
{
    for (int i = 0; i < set->count; i++)
    {
        if (set->data[i] == value)
            return 0; // Ignore duplicate
    }

    if (set->count >= NUMBER_OF_PORTS)
    {
        fprintf(stderr, "Error: Set overflow.\n");
        return -1; 
    }

    if (set->data[set->count - 1] < value)
    {
        set->data[set->count] = value; // Add at the end
        set->count++;
        return 0; // Success
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
void init_port_iterator(port_set_iterator_t *it, const port_set_t *set)
{
    it->set = set;
    it->index = 0;
}

// Manual control over the iterator position
void set_port_iterator_index(port_set_iterator_t *it, int index)
{
    if (index >= 0 && index < it->set->count)
    {
        it->index = index;
    }
    else
    {
        printf("Warning: Iterator index out of bounds.\n");
    }
}

// Fetches the current value and moves the pointer forward
short port_iterator_next(port_set_iterator_t *it, unsigned int *out_value)
{
    if (it->index < it->set->count)
    {
        *out_value = it->set->data[it->index++];
        return 0; // Success
    }
    return -1; // Failure
}
