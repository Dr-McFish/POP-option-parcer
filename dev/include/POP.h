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

int		POP_get_argc();
char**	POP_get_argv();

/* NULL and '\\0' are to be used if the corresponding name is not desired */
void POP_new_bool_opt(bool* output_target, 	char short_name, char* long_name);
/* NULL and '\\0' are to be used if the corresponding name is not desired */
void POP_new_str_opt(char** output_target,	char short_name, char* long_name);
/* NULL and '\\0' are to be used if the corresponding name is not desired */
void POP_new_int_opt(int* output_target,	char short_name, char* long_name);

enum POPparce_return_code{	PARCE_SUCCSEES, PARCE_FAIL, PARCE_FAIL_INVALID_OPT,
							PARCE_FAIL_MISSING_ARG, PARCE_FAIL_NOT_A_NUMBER,
							PARCE_FAIL_DUPLICATE_OPTION};
enum POPparce_return_code POP_parce(int argc, char** argv);


#endif
