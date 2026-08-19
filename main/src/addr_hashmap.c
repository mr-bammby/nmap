#define MODULE_DEBUG DEBUG_ADDR_HASHMAP
#include "debug.h"
#include "addr_hashmap.h"

static uint32_t default_hash_function(uint32_t addr)
{
    return addr;
}

int addr_hashmap_init(addr_hashmap_t *map, size_t size, uint32_t (*hash_func)(uint32_t))
{
    LOGD("Entering add_hashmap_init\n");
    map->entries = calloc(size, sizeof(addr_entry_t));

    if (!map->entries)
    {
        return -1;
    }
    map->size = size;
    map->count = 0;

    if (hash_func == NULL)
    {
        map->hash_func = default_hash_function;
    }
    else
    {
        map->hash_func = hash_func;
    }
    return 0;
}

int addr_hashmap_put(addr_hashmap_t *map, uint32_t addr)
{
    if (!map || !map->entries || !map->hash_func)
    {
        return -1; // Invalid map
    }
    if (map->count >= map->size) {
        return -1; // Hashmap is full
    }
    uint32_t hash = map->hash_func(addr) % map->size;
    while (map->entries[hash].addr != 0)
    {
        if (map->entries[hash].addr == addr)
        {
            return -1; // Address already exists
        }
        hash = (hash + 1) % map->size; // Linear probing
    }
    map->entries[hash].addr = addr;
    map->entries[hash].idx = map->count + 1; // Store the index of the entry
    map->count++;
    return 0;
}

int addr_hashmap_get(const addr_hashmap_t *map, uint32_t addr, uint32_t *idx)
{
    if (!map || !map->entries || !map->hash_func)
    {
        return -1; // Invalid map
    }
    uint32_t hash = map->hash_func(addr) % map->size;
    while (map->entries[hash].addr != 0)
    {
        if (map->entries[hash].addr == addr)
        {
            *idx = map->entries[hash].idx - 1;
            return 0; // Found
        }
        hash = (hash + 1) % map->size; // Linear probing
    }
    return -1; // Not found
}

void addr_hashmap_free(addr_hashmap_t *map)
{
    free(map->entries);
    map->entries = NULL;
    map->size = 0;
    map->count = 0;
    map->hash_func = NULL;
}
