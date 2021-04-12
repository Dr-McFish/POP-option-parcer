#include "linked_list.h"
#include "stdio.h"

bool is_eq_int(int a, int b) {return a == b;}

int main() {
	node_t* list_head = NULL;
	inject_node(&list_head, new_node(1));
	inject_node(&list_head, new_node(2));
	inject_node(&list_head, new_node(3));
	inject_node(&list_head, new_node(4));

	printf("Initilized list\n(1, 2, 3, 4; from head): ");
	printlist(list_head);
	printf("\n");

	printf("last node : %d\n", final_node(list_head)->value);
	printf("\n");

	for (int i = 0; i < 5; i++)
	{
		printf("%dth node:", i);
		node_t* ith_node = nth_node(list_head, i);
		if (ith_node == NULL) printf(" nonexistant\n"); 
		else printf(" %d\n", ith_node->value); 
	}
	printf("\n");

	printf("Addind nodes 7, and 8 after 1th node: ");
	inject_node(&(nth_node(list_head, 1)->next), new_node(7));
	inject_node(&(nth_node(list_head, 1)->next), new_node(8));
	printlist(list_head);
	printf("\n");

	printf("Deleting 2 node: ");
	{
		node_t* searcher = list_head;
		while (searcher != NULL && searcher->next != NULL)
		{
			if (searcher->next->value == 2)
				remove_next(searcher);
			searcher = searcher->next;
		}
	}
	printlist(list_head);
	printf("\n");
	printf("\n");

	printf("Find 9: %s\n", find_node(list_head, 9, &is_eq_int) ? "FOUND!" : "NOT FOUND!");
	node_t* node8 = find_node(list_head, 8, &is_eq_int);
	printf("Find 8: %s\n", node8 ? "FOUND!" : "NOT FOUND!");
	printf("\n");
	
	nuke_tail(&(node8->next));
	printf("Nuked list from 8: ");
	printlist(list_head);

	nuke_tail(&list_head);
	printf("Nuked list from head: ");
	printlist(list_head);
	return 0;
}