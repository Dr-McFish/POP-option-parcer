#ifndef OPTIONS_H
# define OPTIONS_H

#include <stdint.h>
#include <hashmap.h>
#include "generic_option.h"

#define LETTERS_IN_THE_ALPHABET 26
typedef struct	POP_options
{
	option_ptr_t short_names[LETTERS_IN_THE_ALPHABET * 2];
	hashmap_t long_names;
}				POP_options_t;

#endif
