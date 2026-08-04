#ifndef ADDR_HASHTABLE_H
#define ADDR_HASHTABLE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint32_t addr;
    uint32_t idx;
} addr_entry_t;

typedef struct {
    addr_entry_t *entries;
    size_t size;
    size_t count;
    uint32_t (*hash_func)(uint32_t);
} addr_hashmap_t;

/* */
/* Make size 10X bigger than the number of entries for better performance */
int addr_hashmap_init(addr_hashmap_t *map, size_t size, uint32_t (*hash_func)(uint32_t));
void addr_hashmap_free(addr_hashmap_t *map);
int addr_hashmap_put(addr_hashmap_t *map, uint32_t addr);
int addr_hashmap_get(const addr_hashmap_t *map, uint32_t addr, uint32_t *idx);

#endif // ADDR_HASHTABLE_H