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
	printf("[\"%s\" : option_ptr_t]", pair->key);
}

#define PRIME_NUM_A 4297
#define PRIME_NUM_B 5039
#define PRIME_NUM_C 3709
uint64_t strhash_ben_awad(const char* string, uint64_t upper_bound)
{
	uint64_t hash = PRIME_NUM_A;
	int i = 0;

	while(string[i] != '\0'){
		hash = (PRIME_NUM_B * (hash + PRIME_NUM_C) * string[i]) % upper_bound;
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

VALUE_TYPE* lookup(const hashmap_t* map, const char* key){
	key_value_t kv; kv.key = key;
	node_t* rt = find_node(map->list[strhash(key, map->list_len)], &kv, &compare_keys);
	if (rt)
		return (&rt->value.value);
	else
		return NULL;
}

void add_hm(hashmap_t* map, const char* key, VALUE_TYPE new_val)
{
	key_value_t kv; kv.key = key;
	node_t* existing_entry = find_node(map->list[strhash(key, map->list_len)], &kv, &compare_keys);
	if (existing_entry == NULL) {
		kv.value = new_val;
		inject_node(&map->list[strhash(key, map->list_len)], new_node(&kv));
		map->num_of_items++;
	} else {
		existing_entry->value.value = new_val;
	}
}
void add_entry(hashmap_t* map, const char* key, VALUE_TYPE value)
{
	rehash(map);
	add_hm(map, key, value);
}

void rm_entry(hashmap_t* map, const char* key){
	node_t** entry_to_del = (map->list + strhash(key, map->list_len));
	if(entry_to_del == NULL) return;
	else {
		rm_node(entry_to_del);
		map->list_len--;
		/* check if load is very very low, rehash to save memory DONE [x] */
		rehash(map);
	}
}

double calc_load(const hashmap_t* map){
	return (((double)map->num_of_items + 1.0) / ((double)map->list_len));
}

#define MIN_LOAD 0.00125
#define MAX_LOAD 0.8
void rehash(hashmap_t* map)
{
	size_t new_size;
	double load = calc_load(map);

	if (load > MAX_LOAD) {
		new_size = map->list_len * 2;
	} else if (load < MIN_LOAD) {
		new_size = map->list_len / 2;
	} else
		return;
	hashmap_t new_map;
	init_hashmap(&new_map, new_size);
	if (new_map.list == NULL) return;
	for (size_t i = 0; i < map->list_len; i++) {
		node_t* traverce = map->list[i];
		while (traverce != NULL) {
			add_hm(&new_map, traverce->value.key, traverce->value.value);
			traverce = traverce->next;
		}
	}
	cleanup_map(map);
	*map = new_map;
}

void print_map(const hashmap_t* map)
{
	printf("len: %I64d, No of items %I64d, Load: %f \n", map->list_len, map->num_of_items, calc_load(map));
	for (size_t i = 0; i < map->list_len; i++) {
		printf("o -> ");
		printlist(map->list[i]);
		printf("\n");
	}
}