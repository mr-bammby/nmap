#ifndef ADDR_HASHTABLE_H
#define ADDR_HASHTABLE_H

#include <stdint.h>
#include <stdlib.h>

/* Structure representing an entry in the address hashmap */
typedef struct {
    uint32_t addr; // The IPv4 address stored in the entry
    uint32_t idx; // The index of the entry in the hashmap (1-based)
} addr_entry_t;


/* Structure representing an entry in the address hashmap */
typedef struct {
    addr_entry_t *entries; // Pointer to the array of entries
    size_t size; // The total size of the hashmap (number of entries)
    size_t count; // The current number of entries in the hashmap
    uint32_t (*hash_func)(uint32_t); // Pointer to the hash function used for hashing addresses
} addr_hashmap_t;

/* Initialize the address hashmap. */
int addr_hashmap_init(addr_hashmap_t *map, size_t size, uint32_t (*hash_func)(uint32_t)); // Ensure that size is a power of 2 for optimal performance and that size is 10x the expected number of entries to minimize collisions.

/* Free the memory allocated for the address hashmap. */
void addr_hashmap_free(addr_hashmap_t *map);

/* Add an address to the hashmap. */
int addr_hashmap_put(addr_hashmap_t *map, uint32_t addr);

/* Retrieve the index of an address in the hashmap. */
int addr_hashmap_get(const addr_hashmap_t *map, uint32_t addr, uint32_t *idx);

#endif /* ADDR_HASHTABLE_H */