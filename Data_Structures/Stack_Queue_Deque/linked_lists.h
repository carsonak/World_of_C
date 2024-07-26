#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

/**
 * struct single_link_node - a singly linked list node.
 * @next: pointer to the next node.
 * @data: data that the node holds.
 */
typedef struct single_link_node
{
	void *data;
	struct single_link_node *next;
} single_link_nd;

/**
 * struct double_link_node - a doubly linked list node.
 * @next: pointer to the next node.
 * @prev: pointer to the previous node.
 * @data: data that the node holds.
 */
typedef struct double_link_node
{
	void *data;
	struct double_link_node *next;
	struct double_link_node *prev;
} double_link_nd;

#endif /* LINKED_LISTS_H */
