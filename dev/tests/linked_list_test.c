#include "linked_list.h"
#include "stdio.h"

bool is_eq_int(int a, int b) {return a == b;}

int main() {
	node_t* list_head = NULL;
	key_value_t i;
	i.value = 1;
	i.key = "1";
	inject_node(&list_head, new_node(&i)); i.value++; i.key = "2";
	inject_node(&list_head, new_node(&i)); i.value++; i.key = "3";
	inject_node(&list_head, new_node(&i)); i.value++; i.key = "4";
	inject_node(&list_head, new_node(&i));

	printf("Initilized list\n(1, 2, 3, 4; from head)\t\t\t o-> ");
	printlist(list_head);
	printf("\n");
	printf("\n");

	printf("last node :"); print_kv_pair(&final_node(list_head)->value);
	printf("\n\n");

	for (int i = 0; i < 5; i++)
	{
		printf("%dth node:", i);
		node_t* ith_node = nth_node(list_head, i);
		if (ith_node == NULL) printf(" nonexistant\n"); 
		else print_kv_pair(&ith_node->value);
		printf("\n");
	}
	printf("\n");

	printf("Addind nodes 7, and 8 after 1th node \to -> ");
	i.key = "7"; i.value = 7;
	inject_node(&(nth_node(list_head, 1)->next), new_node(&i)); i.value++; i.key = "8";
	inject_node(&(nth_node(list_head, 1)->next), new_node(&i)); 
	printlist(list_head);
	printf("\n");

	i.key = "2";
	printf("Deleting 2 node \t\t\to -> ");
	rm_node(find_node_meteptr(&list_head, &i, &compare_keys));
	printlist(list_head);
	printf("\n");
	printf("\n");

	i.key = "9";
	printf("Find 9: %s\n", find_node(list_head, &i, &compare_keys) ? "FOUND!" : "NOT FOUND!");
	i.key = "8";
	node_t* node8 = find_node(list_head, &i, &compare_keys);
	printf("Find 8: %s\n", node8 ? "FOUND!" : "NOT FOUND!");
	printf("\n");
	
	nuke_tail(find_node_meteptr(&list_head, &i, &compare_keys));
	printf("Nuked list from 8 \t\t\to -> ");
	printlist(list_head);
	printf("\n");

	nuke_tail(&list_head);
	printf("Nuked list from head \t\t\to-> ");
	printlist(list_head);
	printf("\n");
	return 0;
}