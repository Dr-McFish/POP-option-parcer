#include <stdio.h>
#include "POP/POP.h"

int main(int argc, char *argv[])
{
	enum POPparce_return_code exit_code;
	POP_opts_init();

	bool opt_help = false;		/* -h, --help		*/
	POP_new_bool_opt(&opt_help, 'h', "help");

	char* opt_name = NULL;		/* --name 			*/
	POP_new_str_opt(&opt_name, '\0', "name");

	int opt_age = -1;			/* -n				*/
	POP_new_int_opt(&opt_age, '\0', "age");

	char* opt_message = NULL;	/* -m --message		*/
	POP_new_str_opt(&opt_message, 'm', "message");

	int opt_favorite_number = -1;/* -n				*/
	POP_new_int_opt(&opt_favorite_number, 'n', NULL);

	bool opt_loves_onions = false;	/* --love-onions -O	*/
	bool opt_hates_onions = false;	/* --hate-onions -o	*/
	POP_new_bool_opt(&opt_loves_onions, 'O', "love-onions");
	POP_new_bool_opt(&opt_hates_onions, 'o', "hate-onions");

	bool opt_shoes = false;		/* -s */
	bool opt_socks = false; 	/* -c */
	POP_new_bool_opt(&opt_shoes, 's', "shoes");
	POP_new_bool_opt(&opt_socks, 'c', "socks");


	exit_code = POP_parce(argc, argv);
	if (exit_code != PARCE_SUCCSEES) {
		return -1;
	}
	if(opt_loves_onions && opt_hates_onions){
		fprintf(stderr, "Incompatible options: --love-onions, --hate-onions\n");
		return -1;
	}
	argc = POP_get_argc();
	argv = POP_get_argv();

	if (opt_help){
		/* DISCLAIMER: this library doest provide any elegant way to display	*\
		\* a help message, this is just for demonstrative purposes				*/
		printf("SYNOPSIS:\n\tprofile [OPTIONS] [FAVORITE FRUIT...]\n\n");
		printf("DESCRIPTION:\n\n");
		printf("\tGenerates a profile based on the OPTIONS and your list of favorite fruit\n\n");
		printf("\t-h, --help\t\tDisplay this help message and quit\n\n");
		printf("\t--name [NAME]\t\tAdd your name to your profile\n\n");
		printf("\t--age [AGE]\t\tAdd your age to your profile\n\n");
		printf("\t--message [MESSAGE],\tAdd your message to your profile\n\t-m [MESSAGE]\n\n");
		printf("\t-O, --love-onions\tIndicate weather you love or hate onions.\n");
		printf("\t-o, --hate-onions\tThere is no middle ground.\n\n");
		printf("\t-c, --socks\t\tIndicate that you are wearing socks\n\n");
		printf("\t-s, --shoes\t\tIndicate that you are wearing shoes\n\n");
		printf("EXAMPLE USAGE:\n\n");
		printf("\t$ %s --name Bob apples\n", argv[0]);
		printf("\tPROFILE: \n\t\tYour name is Bob\n\t\tYour favorite fruit are:\n\t\t1. aplles\n");
		return 0;
	}
	
	printf("\nPROFILE:\n\n");
	if(opt_name)
		printf("Your name is %s\n", opt_name);
	if (opt_age != -1)
		printf("You are %d years old\n", opt_age);
	if(opt_message)
		printf("Your message to the world is: \"%s\"\n", opt_message);
	if (opt_favorite_number != -1)
		printf("Your favorite number is %d\n", opt_favorite_number);
	if (opt_hates_onions)
		printf("You hate onions.\n");
	else if (opt_loves_onions)
		printf("You LOVE onions.\n");
	if(opt_shoes)
		printf("You are wearing shoes\n");
	if(opt_socks)
		printf("You are wearing socks\n");
	if (argc > 1){
		printf("Your favorite fruit are:\n");
		for (int i = 1; i < argc; i++) {
			printf("  %2d. %s\n", i, argv[i]);
		}
	}
	
	void POP_opts_cleanup();
	return 0;
}
