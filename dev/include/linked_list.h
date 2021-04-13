/* For compiling the library only!!! */
/* if to be on ists own and the data type doesn't mach up it will not work*/
#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdint.h>
# include <stdbool.h>
#include "kv_pair.h"

typedef key_value_t NODE_DATA;
typedef struct	node {
	NODE_DATA value;
	struct node* next;
}				node_t;

typedef bool(*is_eq_data_f)(const NODE_DATA* a, const NODE_DATA* b);
node_t** find_node(node_t* haystack, NODE_DATA* needle, is_eq_data_f is_eq);
node_t* new_node(NODE_DATA* value);
node_t* nth_node(node_t* head, uint16_t n);
node_t* final_node(node_t* head);
node_t* inject_node(node_t** old_node, node_t* new_node);
/* ptr MUST be the a pointer to the link from the previus
 * ellement to the item to be deleted. If it is not a pointer
 * from the prevevius element, it will break the list, causing
 * a memory leak and posibly leaving acces to no longer 
 * owned memory 
 */
void rm_node(node_t** ptr);
void nuke_tail(node_t** head);

#endif