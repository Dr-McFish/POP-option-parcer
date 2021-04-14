#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hashmap.h"
#include "primes.h"
#include "eq_str.h"

#include <stdio.h>


void set_kv_pair(key_value_t* pair, const char* key, VALUE_TYPE value){
	pair->key = key;
	pair->value = value;
}
bool compare_keys(const key_value_t* a, const key_value_t* b){
	return(eq_str(a->key, b->key));
}
void print_kv_pair(const key_value_t* pair)
{
	printf("[\"%s\" : %I64u]", pair->key, pair->value);
}

#define PRIME_NUM 17
uint64_t strhash_ben_awad(const char* string, uint64_t upper_bound)
{
	uint64_t hash = PRIME_NUM;
	uint64_t bigprime = next_prime(upper_bound * 21);
	int i = 0;

	while(string[i] != '\0'){
		hash = (bigprime * (hash + i) * string[i]) % upper_bound;
		i++;
	}
	return(hash);
}
uint64_t strhash(const char* string, uint64_t upper_bound)
{
	return strhash_ben_awad(string, upper_bound);
}

void init_hashmap(hashmap_t* map, size_t reserve)
{
	reserve = next_prime(reserve);
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

node_t** _lookup_adr(const hashmap_t* map, const char* key)
{
	key_value_t kv_pair; kv_pair.key = key;
	uint64_t hash = strhash(key, map->list_len);
	node_t** haystack = map->list + hash;
	node_t** rt;
	rt = find_node_meteptr(haystack, &kv_pair, &compare_keys);
	return(rt);
}

const VALUE_TYPE* lookup(const hashmap_t* map, const char* key){
	key_value_t kv; kv.key = key;
	node_t* rt = find_node(map->list[strhash(key, map->list_len)], &kv, &compare_keys);
	if (rt)
		return (&rt->value.value);
	else
		return NULL;
	/*
	node_t* haystack = map->list[strhash(key, map->list_len)];
	key_value_t needle; needle.key = key;
	if (haystack) {
		return &(haystack->value.value);
	} else
		return NULL; */
}

void add_hm(hashmap_t* map, const char* key, VALUE_TYPE new_val)
{
	/* check load, if load is too high, rehash TODO [ ] */
	key_value_t kv; kv.key = key;
	node_t* existing_entry = find_node(map->list[strhash(key, map->list_len)], &kv, &compare_keys);
	if (existing_entry == NULL) {
		/* create new entry DONE [x]*/
		kv.value = new_val;
		inject_node(&map->list[strhash(key, map->list_len)], new_node(&kv));
		map->num_of_items++;
	} else {
		/* replace existing contents DONE [x] */
		existing_entry->value.value = new_val;
	}
}

void rm_entry(hashmap_t* map, const char* key){
	node_t** entry_to_del = _lookup_adr(map, key);
	if(entry_to_del == NULL) return;
	else {
		rm_node(entry_to_del);
		map->list_len--;
		/* check if load is very very low, rehash to save memory TODO [ ] */
	}
}

float calc_load(const hashmap_t* map){
	return ((float)map->num_of_items / (float)map->list_len);
}

#define MIN_LOAD 0.001f
#define MAX_LOAD 0.8f
bool elegible_for_rehash(const hashmap_t* map)
{
	float load = calc_load(map);
	return(load > MAX_LOAD || load < MIN_LOAD);
}

void print_map(const hashmap_t* map)
{
	printf("len: %I64d, No of items %I64d\n", map->list_len, map->num_of_items);
	for (size_t i = 0; i < map->list_len; i++) {
		printf("o -> ");
		printlist(map->list[i]);
		printf("\n");
	}
}