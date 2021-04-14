#include "hashmap.h"
#include <stdio.h>

int main()
{
	hashmap_t my_map;
	init_hashmap(&my_map, 7);

	printf("\n\n\n");
	printf("Empty map:\n");
	print_map(&my_map);
	printf("\n");

	add_hm(&my_map, "Code", 1337);
	print_map(&my_map);
	const VALUE_TYPE* looked_up_vall = lookup(&my_map, "Code");
	printf("\n");
	if(looked_up_vall != NULL) printf("Add entry 'Code': %I64d, \n", *looked_up_vall);
	printf("misspelled lookup: %p\n", lookup(&my_map, "code"));
	printf("\n");

	add_hm(&my_map, "Number of dolas", 1000000);
	add_hm(&my_map, "lines of code", 420);
	print_map(&my_map);
	printf("\n");

	looked_up_vall = lookup(&my_map, "Number of dolas");
	if(looked_up_vall != NULL) printf("\"%s\" : %I64d, \n", "Number of dolas", *looked_up_vall);
	printf("\n");

	looked_up_vall = lookup(&my_map, "lines of code");
	if(looked_up_vall != NULL) printf("\"%s\" : %I64d, \n", "lines of code", *looked_up_vall);
	printf("\n");
	add_hm(&my_map, "a", 1);
	add_hm(&my_map, "b", 1);
	add_hm(&my_map, "c", 1);
	add_hm(&my_map, "d", 1);
	add_hm(&my_map, "e", 1);
	add_hm(&my_map, "f", 1);
	add_hm(&my_map, "g", 1);
	add_hm(&my_map, "h", 1);
	print_map(&my_map);

	cleanup_map(&my_map);
	return 0;
}