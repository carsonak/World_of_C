#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

#include <stdlib.h> /* *alloc */

/**
 * dup_func - a function that returns a copy of an object, NULL on failure.
 */
typedef void *(dup_func)(void *const);

/**
 * delete_func - a function that deletes an object.
 */
typedef void(delete_func)(void *const);

/*singly linked list*/

typedef struct single_link_node single_link_node;

single_link_node *sln_new(void *const data, dup_func *duplicate_data);
single_link_node *sln_insert_after(
	single_link_node *const node, single_link_node *const this_node);
void *sln_remove(single_link_node *node);
void *sln_get_data(const single_link_node *node);
single_link_node *sln_get_next(const single_link_node *node);

/*doubly linked list*/

typedef struct double_link_node double_link_node;

double_link_node *dln_new(void *const data, dup_func *duplicate_data);
double_link_node *dln_insert_after(
	double_link_node *const this_node, double_link_node *const node);
void *dln_remove(double_link_node *node);
void *dln_get_data(const double_link_node *node);
double_link_node *dln_get_next(const double_link_node *node);
double_link_node *dln_get_previous(const double_link_node *node);

#endif /* LINKED_LISTS_H */
