#include <stdlib.h>
#include <stdio.h>
#include "POP.h"
#include "options.h"
#include "error.h"

POP_options_t* g_POP_options;
int		g_POPargc;
char**	g_POPargv;
int		g_POParg_array_size;
//error_t	g_error; use asprintf?

int		POP_get_argc() {return g_POPargc;}
char**	POP_get_argv() {return g_POPargv;}

void POP_opts_init() {
	g_POP_options = malloc(sizeof(POP_options_t));
	init_hashmap(&g_POP_options->long_names, 10);
	option_ptr_t template;
		template.opt_ptr = NULL;
		template.type = UNASIGED_OPT;
	for (int i = 0; i < LETTERS_IN_THE_ALPHABET *2; i++) {
		g_POP_options->short_names[i] = template;
	}

	g_POParg_array_size = 10;
	g_POPargc = 0;
	g_POPargv = malloc(sizeof(*g_POPargv) * g_POParg_array_size);
	//g_error = NULL;
}

void POP_opts_cleanup(){
	cleanup_map(&g_POP_options->long_names);
	free(g_POP_options);
	free(g_POPargv);
	//free(g_error);
}

int POP_letter_to_index(char c)
{
	if ('a' <= c && c <= 'z')
		return (c - 'a');
	if ('A' <= c && c <= 'Z')
		return ((c - 'A') + ('z' - 'a'));
	else
		return -1;
}

void POP_add_arg(char* arg) {
	if(g_POPargc == (g_POParg_array_size - 1)) {
		g_POParg_array_size *= 2;
		realloc(g_POPargv, g_POParg_array_size);
	}
	g_POPargv[g_POPargc] = arg;
	g_POPargc++;
}

void POP_new_bool_opt(bool* output_target, char short_name, char* long_name)
{
	option_ptr_t template;
		template.opt_ptr = output_target;
		template.type = BOOL_OPT;
		template.was_used = false;
	if (POP_letter_to_index(short_name) != -1)
		g_POP_options->short_names[POP_letter_to_index(short_name)] = template;
	if (long_name)
		add_entry(&g_POP_options->long_names, long_name, template);
}


void POP_new_str_opt(char** output_target,	char short_name, char* long_name)
{
	option_ptr_t template;
		template.opt_ptr = output_target;
		template.type = STRING_OPT;
		template.was_used = false;
	if (POP_letter_to_index(short_name) != -1)
		g_POP_options->short_names[POP_letter_to_index(short_name)] = template;
	if (long_name)
		add_entry(&g_POP_options->long_names, long_name, template);
}

void POP_new_int_opt(int* output_target,	char short_name, char* long_name)
{
	option_ptr_t template;
		template.opt_ptr = output_target;
		template.type = INT_OPT;
		template.was_used = false;
	if (POP_letter_to_index(short_name) != -1)
		g_POP_options->short_names[POP_letter_to_index(short_name)] = template;
	if (long_name)
		add_entry(&g_POP_options->long_names, long_name, template);
}

void POP_print_error(char* long_name, char short_name, enum POPparce_return_code code, char* next_arg)
{
	switch (code)
	{
	case PARCE_SUCCSEES:
		break;
	case PARCE_FAIL:
		fprintf(stderr, "PARCE ERROR: Generic error\n");
		break;
	case PARCE_FAIL_INVALID_OPT:
		fprintf(stderr, "PARCE ERROR %s-%c is not a valid option\n",
		long_name? long_name : "", short_name? short_name : '\b');
		break;
	case PARCE_FAIL_DUPLICATE_OPTION:
		fprintf(stderr, "PARCE ERROR: The option %s-%c is used twice\n",
		long_name? long_name : "", short_name? short_name : '\b');
		break;
	case PARCE_FAIL_MISSING_ARG:
		fprintf(stderr, "PARCE ERROR: option %s-%c requires an argument after it\n",
		long_name? long_name : "", short_name? short_name : '\b');
		break;
	case PARCE_FAIL_NOT_A_NUMBER:
		fprintf(stderr, "PARCE ERROR: argument of %s-%c, \"%s\", is not a number\n",
		long_name? long_name : "", short_name? short_name : '\b', next_arg);
		break;
	default:
		break;
	}
}

bool POP_is_decimal_number(const char* str){
	for (int i = 0;str[i] != '\0'; i++)
		if ( !('0' <= str[i] && str[i] <= '9') )
			return false;
	return true;
}

enum POPparce_return_code POP_handle_opt(option_ptr_t* target_opt, char* next_arg)
{
	switch (target_opt->type) {
		case UNASIGED_OPT:
			return PARCE_FAIL_INVALID_OPT;
			break;
		case BOOL_OPT:
			*(bool*)target_opt->opt_ptr = true;
			break;
		case STRING_OPT:
		case INT_OPT:
			if (next_arg == NULL || next_arg[0] == '-') /* no next arg or next arg is an option*/
				return PARCE_FAIL_MISSING_ARG;
			if (target_opt->type == STRING_OPT)
				*(char**)target_opt->opt_ptr = next_arg;
			else /* INT OPT */ {
				if(!POP_is_decimal_number(next_arg))
					return PARCE_FAIL_NOT_A_NUMBER;
				*(int*)target_opt->opt_ptr = atoi(next_arg);
			}
			break;
	}
	if(target_opt->was_used)
		return PARCE_FAIL_DUPLICATE_OPTION;
	else
		target_opt->was_used = true;	
	return PARCE_SUCCSEES;
}

enum POPparce_return_code POP_parce(int argc, char** argv)
{
	option_ptr_t* target_opt;
	enum POPparce_return_code parce_code;

	POP_add_arg(argv[0]);
	int skip_next_arg_opt = 0;
	for (int i = 1; i < argc; i += skip_next_arg_opt + 1)
	{
		skip_next_arg_opt = 0;
		if (argv[i][0] == '-') {
			/* option */
			if (argv[i][1] == '-') {
				/* long option */
				target_opt = lookup(&g_POP_options->long_names, argv[i] + 2);
				skip_next_arg_opt = (	target_opt->type == STRING_OPT
									||	target_opt->type == INT_OPT) ? 1 : 0;
				if(target_opt == NULL) return PARCE_FAIL_INVALID_OPT; /* TODO: add error logging system */
				parce_code = POP_handle_opt(target_opt, ( ((i+1) < argc ) ? argv[i + 1] : NULL));
				if (parce_code != PARCE_SUCCSEES){
					POP_print_error(argv[i], '\0', parce_code, argv[i + 1]);
					return parce_code;
				}
			} else {
				/* short options */
				int j = 1;
				while (argv[i][j] != '\0') {
					target_opt = g_POP_options->short_names + POP_letter_to_index(argv[i][j]);
					skip_next_arg_opt = (	target_opt->type == STRING_OPT
										||	target_opt->type == INT_OPT
										||  skip_next_arg_opt == 1) ? 1 : 0;
					parce_code = POP_handle_opt(target_opt, ( ((i+1) < argc ) ? argv[i + 1] : NULL));
					if (parce_code != PARCE_SUCCSEES) {
						POP_print_error(NULL, argv[i][j], parce_code, argv[i + 1]);
						return parce_code;
					}
					j += 1;
				}
			}
		} else {
			/* argument */
			POP_add_arg(argv[i]);
		}
	}
	return PARCE_SUCCSEES;
}