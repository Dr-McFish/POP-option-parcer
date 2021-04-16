#include "POP.h"
#include <stdio.h>

//void log_f(const char* str);

int main(int argc, char *argv[])
{
	enum POPparce_return_code exit_code;
	POP_opts_init();

	bool opt_help = false;			/* -h, --help		*/
	POP_new_bool_opt(&opt_help, 'h', "help");

	char* opt_name = NULL;		/* -m --message		*/
	POP_new_str_opt(&opt_name, '\0', "name");

	char* opt_message = NULL;		/* -m --message		*/
	POP_new_str_opt(&opt_message, 'm', "message");

	int opt_favorite_number = -1;	/* -n				*/
	POP_new_int_opt(&opt_favorite_number, 'n', NULL);

	bool opt_loves_onions = false;	/* --love-onions -O	*/
	bool opt_hates_onions = false;	/* --hate-onions -o	*/
	POP_new_bool_opt(&opt_loves_onions, 'O', "love-onions");
	POP_new_bool_opt(&opt_hates_onions, 'o', "hate-onions");

	exit_code = POP_parce(argc, argv);
	if (exit_code != PARCE_SUCCSEES) {
		fprintf(stderr, "Parce error, code: %d\n", exit_code); /* TODO */
		return -1;
	}
	if(opt_loves_onions && opt_hates_onions){
		fprintf(stderr, "Incompatible options: --love-onions, --hate-onions\n");
		return -1;
	}

	if (opt_help){
		printf("help message\n"); /* TODO */
		printf("USAGE: profile [OPTIONS] [FAVORITE THINGS...]\n");
		return 0;
	}
	
	printf("PROFILE:\n");
	if(opt_name)
		printf("Your name is %s\n", opt_name);
	if(opt_message)
		printf("Your message to the world is: \"%s\"\n", opt_message);
	if (opt_hates_onions)
		printf("You hate onions.\n");
	else if (opt_loves_onions)
		printf("You LOVE onions.\n");
	if (opt_favorite_number != -1) /* TODO */
		printf("Your favorite number is %d\n", opt_favorite_number);
	argc = POP_get_argc();
	argv = POP_get_argv();
	if (argc > 1){
		printf("Your favorite thigs are:\n");
		for (int i = 1; i < argc; i++) {
			printf("  %2d. %s\n", i, argv[i]);
		}
		
	}
	
	void POP_opts_cleanup();
	return 0;
}
