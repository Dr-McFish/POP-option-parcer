#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hashmap.h"
#include "primes.h"
#include "eq_str.h"

void set_keyvalue(key_value_t* pair, const char* key, VALUE_TYPE value){
	pair->key = key;
	pair->value = value;
}
bool compare_keys(key_value_t* a, key_value_t* b){
	return(eq_str(a->key, b->value));
}

void init_hashmap(hashmap_t* map, size_t reserve)
{
	reserve = next_prime( reserve < 200 ? (size_t)(reserve * 1.25) : reserve);
	map->list = malloc(sizeof(map->list[0]) * reserve);
	if (map->list) {
		map->list_len = reserve;
		for (size_t i = 0; i < reserve; i++) {
			map->list[i] = NULL;
		}
	} else
		map->list_len = 0;
	map->num_of_items = 0;
}

void cleanup_map(hashmap_t* map)
{
	if (map->list == NULL) return;
	for (size_t i = 0; i < map->list_len; i++) {
		nuke_tail(map->list + i);
	}
	free(map->list);
	map->list = NULL;
	map->list_len = 0;
	map->num_of_items = 0;
}

float calc_load(const hashmap_t* map){
	return ((float)map->num_of_items / (float)map->list_len);
}

node_t* lookup(const hashmap_t* map, const char* key, VALUE_TYPE value)
{
	uint64_t keyhash = strhash(key);
	key_value_t* kv_pair = malloc(sizeof(key_value_t));
	set_keyvalue(kv_pair, key, value);
	return(find_node(map->list[keyhash % map->list_len], kv_pair, &compare_keys));
}

void add_element(hashmap_t* map, const char* key, VALUE_TYPE value) {
	
}