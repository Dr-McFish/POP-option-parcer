#ifndef HASHMAP_H
# define HASHMAP_H

#include <stdint.h>
#include <stdbool.h>
#include "kv_pair.h"
#include "linked_list.h"

typedef struct	hashmap
{
	node_t** list;
	size_t list_len;
	size_t num_of_items; 
}				hashmap_t;

//size_t next_prime(size_t n);
uint64_t strhash(const char* string, uint64_t upper_bound);
void init_hashmap(hashmap_t* map, size_t reserve);
void cleanup_map(hashmap_t* map);
void rehash(hashmap_t* map);
//float calc_load(const hashmap_t* map);
void save_data(hashmap_t* map, const char* key, VALUE_TYPE value);
void rm_entry(hashmap_t* map, const char* key);
VALUE_TYPE lookup(const hashmap_t* map, const char* key);
void print_map(const hashmap_t* map);

#endif
