#ifndef OPTIONS_H
# define OPTIONS_H

#include <stdint.h>
#include <stdbool.h>
#include <hashmap.h>
#include "generic_option.h"

#define LETTERS_IN_THE_ALPHABET 26
typedef struct	POP_options
{
	generic_option_t short_names[LETTERS_IN_THE_ALPHABET * 2];
	hashmap_t long_names;
}				POP_options_t;

typedef struct	bool_option
{
	bool* value;
	enum bool_opt_type{FALSE_TYPE, TRUE_TYPE} type;
}				bool_opt_t;
typedef char** str_option_t;
typedef int* it_option_t;

#endif
