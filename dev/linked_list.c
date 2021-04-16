#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

node_t* nth_node(node_t* head, uint16_t n){
	if(n == 0) return head;
	else if(head == NULL) return NULL;
	else return nth_node(head->next, n - 1);
}
node_t* final_node(node_t* head)
{
	if (head == NULL) return NULL;
	else if (head->next == NULL) return head;
	else return final_node(head->next);
}

node_t* new_node(NODE_DATA* value) {
	node_t* rt = malloc(sizeof(node_t));
	if (rt == NULL) return NULL;
	rt->next = NULL;
	rt->value = *value;
	return rt;
}
node_t* find_node(node_t* haystack, NODE_DATA* needle, is_eq_data_f is_eq) {
	while (haystack != NULL)
	{
		if (is_eq(&haystack->value, needle))
			return haystack;
		haystack = haystack->next;
	}
	return NULL;
}
node_t** find_node_meteptr(node_t** haystack, NODE_DATA* needle, is_eq_data_f is_eq) {
	node_t** metaptr = haystack;

	while (haystack != NULL)
	{
		if (is_eq(&((*haystack)->value), needle))
			return metaptr;
		metaptr = &((*haystack)->next);
		haystack = &((*haystack)->next);
	}
	return NULL;
}
node_t* inject_node(node_t** old_node, node_t* new_node) {
	if(new_node == NULL) return (*old_node);
	node_t* temp_ptr = (*old_node);
	(*old_node) = new_node;
	new_node->next = temp_ptr;
	return new_node;
}
void rm_node(node_t** ptr){
	if (ptr == NULL || *ptr == NULL) return;
	node_t* temp_ptr = (*ptr)->next;
	free(*ptr);
	(*ptr) = temp_ptr;
}
void nuke_tail(node_t** head) {
	node_t* temp_ptr = *head;
	node_t* temp_ptr2;
	while (temp_ptr)
	{
		temp_ptr2= temp_ptr->next;
		free(temp_ptr);
		temp_ptr = temp_ptr2;
	}
	(*head) = NULL;
}

void printlist(node_t* head){
	if(head == NULL){
		printf("NULL");
		return;
	}
	print_kv_pair(&head->value);
	printf(" -> ");
	printlist(head->next);
}
