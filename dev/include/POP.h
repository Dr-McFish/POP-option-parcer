/*                      ~ POP Option Parser Library ~                 O    *\
|*     POP.h                                                  \   \   o    *|
|*     By: Dr McFish                                           />|° >°     *|
|*     www.github.com/dr-mcfish                               /   /  bloop *|
\*                                                                         */
#ifndef POP_H
# define POP_H

#include <stdint.h>
#include <stdbool.h>

void POP_opts_init();
void POP_opts_cleanup();

/* NULL and '\\0' are to be used if the corresponding name is not desired */
void POP_new_bool_opt(bool* output_target, 	char short_name, char* long_name);
/* NULL and '\\0' are to be used if the corresponding name is not desired */
void POP_new_str_opt(char** output_target,	char short_name, char* long_name);
/* NULL and '\\0' are to be used if the corresponding name is not desired */
void POP_new_int_opt(int* output_target,	char short_name, char* long_name);

enum POPparse_return_code{	PARSE_SUCCESSES, PARSE_FAIL, PARSE_FAIL_INVALID_OPT,
							PARSE_FAIL_MISSING_ARG, PARSE_FAIL_NOT_A_NUMBER,
							PARSE_FAIL_DUPLICATE_OPTION};
enum POPparse_return_code POP_parse(int argc, char** argv);

int		POP_get_argc();
char**	POP_get_argv();


#endif
