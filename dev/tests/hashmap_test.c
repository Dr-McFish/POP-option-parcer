#include "hashmap.h"
#include <stdio.h>

int main()
{
	hashmap_t my_map;
	printf("cool beans\n");
	init_hashmap(&my_map, 7);

	printf("Empty map:\n");
	print_map(&my_map);

	cleanup_map(&my_map);
	return 0;
}