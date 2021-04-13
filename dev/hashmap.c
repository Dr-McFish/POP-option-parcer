#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
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

#define PRIME_NUM_A 17
//#define PRIME_NUM_B 13
uint64_t strhash_ben_awad(const char* string, uint64_t upper_bound)
{
	uint64_t hash = PRIME_NUM_A;
	uint64_t bigprime = next_prime(upper_bound / 3);

	while(*string != '\0'){
		hash = (bigprime * hash * *string) % upper_bound;
	}
	return(hash);
}
uint64_t strhash(const char* string, uint64_t upper_bound)
{
	return strhash_ben_awad(string, upper_bound);
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

node_t* _lookup_adr(const hashmap_t* map, const char* key)
{
	key_value_t kv_pair; kv_pair.key = key;
	return(*find_node(map->list[strhash(key, map->list_len)], &kv_pair, &compare_keys));
}
VALUE_TYPE lookup(const hashmap_t* map, const char* key) {
	return (_lookup_adr(map, key)->value.value);
}

void save_data(hashmap_t* map, const char* key, VALUE_TYPE new_val)
{
	/* check load, if load is too high, rehash TODO [ ] */
	node_t* existing_entry = _lookup_adr(map, key);
	if (existing_entry == NULL) {
		/* create new entry DONE [x]*/
		inject_node(map->list[strhash(key, map->list_len)], new_node(new_val));
		map->num_of_items++;
	} else {
		/* replace existing contents DONE [x] */
		existing_entry->value.value = new_val;
	}
}

void rm_entry(hashmap_t* map, const char* key, VALUE_TYPE value){
	node_t* entry_to_del = _lookup_adr(map, key);
	if(entry_to_del == NULL) return;
	else {
		rm_node(&entry_to_del);
		map->list_len--;
		/* check if load is very very low, rehash to save memory TODO [ ] */
	}
}