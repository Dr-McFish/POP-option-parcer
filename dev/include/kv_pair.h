#ifndef KV_PAIR_H
# define KV_PAIR_H

#include <stdint.h>

typedef int64_t VALUE_TYPE;
typedef struct	key_value_pair
{
	const char* key;
	VALUE_TYPE value;
}				key_value_t;
void set_kv_pair(key_value_t* pair, const char* key, VALUE_TYPE value);
key_value_t new_kv_pair(const char* key, VALUE_TYPE value);
void print_kv_pair(const key_value_t* pair);
bool compare_keys(const key_value_t* a, const key_value_t* b);

#endif