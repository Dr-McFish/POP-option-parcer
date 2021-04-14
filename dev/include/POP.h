#ifndef POP_H
# define POP_H

#include <stdint.h>
#include <stdbool.h>

void POP_opts_init();
void POP_opts_cleanup();

void non_opt_args(int* argc_targer, char*** argv_target);
//void cleanup_non_opt_args();

/* "\\0" and '\\0' are to be used if the corresponding name is not desired */
void new_bool_opt(bool* output_target,	char true_short_name, char* true_long_name,
										char false_short_name, char* false_long_name);
/* "\\0" and '\\0' are to be used if the corresponding name is not desired */
void new_str_opt(char** output_target,	char short_name, char* long_name);
/* "\\0" and '\\0' are to be used if the corresponding name is not desired */
void new_int_opt(int* output_target,	char short_name, char* long_name);

void parce(int argc, char** argv);

#endif
