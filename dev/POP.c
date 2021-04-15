#include "POP.h"
#include "options.h"
#include "stdlib.h"

//#include "stdio.h"
//void log_f(const char* str) {	printf("%s\n", str); }

POP_options_t* g_POP_options;
int		g_POPargc;
char**	g_POPargv;
int		g_POParg_array_size;

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
}

void POP_opts_cleanup(){
	cleanup_map(&g_POP_options->long_names);
	free(g_POP_options);
	free(g_POPargv);
}

int letter_to_index(char c)
{
	if ('a' <= c && c <= 'z')
		return (c - 'a');
	if ('A' <= c && c <= 'Z')
		return (c - 'A');
	else
		return -1;
}

void add_POP_arg(char* arg) {
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
	if (letter_to_index(short_name) != -1){
		g_POP_options->short_names[letter_to_index(short_name)] = template;
	}if (long_name){
		add_entry(&g_POP_options->long_names, long_name, template);
	}
}


void POP_new_str_opt(char** output_target,	char short_name, char* long_name)
{
	option_ptr_t template;
		template.opt_ptr = output_target;
		template.type = STRING_OPT;
		template.was_used = false;
	if (letter_to_index(short_name) != -1)
		g_POP_options->short_names[letter_to_index(short_name)] = template;
	if (long_name)
		add_entry(&g_POP_options->long_names, long_name, template);
}

void POP_new_int_opt(int* output_target,	char short_name, char* long_name)
{
	option_ptr_t template;
		template.opt_ptr = output_target;
		template.type = INT_OPT;
		template.was_used = false;
	if (letter_to_index(short_name) != -1)
		g_POP_options->short_names[letter_to_index(short_name)] = template;
	if (long_name)
		add_entry(&g_POP_options->long_names, long_name, template);
}



bool is_decimal_number(const char* str){
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
		case BOOL_OPT:
			*(bool*)target_opt->opt_ptr = true;
			break;
		case STRING_OPT:
		case INT_OPT:
			if (next_arg == NULL || next_arg[0] == '-') /* is last arg or next arg is an option*/
				return PARCE_FAIL_MISSING_ARG;
			if (target_opt->type == STRING_OPT)
				*(char**)target_opt->opt_ptr = next_arg;
			else /* INT OPT */ {
				if(!is_decimal_number(next_arg))
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

	add_POP_arg(argv[0]);
	int skip_next_arg_opt = 0;
	for (int i = 1; i < argc; i += skip_next_arg_opt + 1)
	{
		skip_next_arg_opt = 0;
		if (argv[i][0] == '-') {
			/* option */
			if (argv[i][1] == '-') {
				/* long option */
				target_opt = lookup(&g_POP_options->long_names, argv[i] + 2);
				if(target_opt == NULL) return PARCE_FAIL_INVALID_OPT; /* TODO: add error logging system */
				parce_code = POP_handle_opt(target_opt, ( ((i+1) < argc ) ? argv[i + 1] : NULL));
				if (parce_code != PARCE_SUCCSEES) return parce_code;
			} else {
				/* short options */
				int j = 1;
				while (argv[i][j] != '\0') {
					target_opt = &g_POP_options->short_names[j];
					int skip_next_arg_opt = (	target_opt->type == STRING_OPT
											||	target_opt->type == INT_OPT
											||  skip_next_arg_opt == 1) ? 1 : 0;
					parce_code = POP_handle_opt(target_opt, ( ((i+1) < argc ) ? argv[i + 1] : NULL));
					if (parce_code != PARCE_SUCCSEES) return parce_code;
					j += 1;
				}
			}
		} else {
			/* argument */
			add_POP_arg(argv[i]);
		}
	}
	return PARCE_SUCCSEES;
}