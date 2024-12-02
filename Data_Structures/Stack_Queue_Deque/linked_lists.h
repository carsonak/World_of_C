#ifndef LINKED_NODES_H
#define LINKED_NODES_H

#include <stdlib.h> /* *alloc */
#include <stdio.h>	/* *printf */

/**
 * dup_func - a function that returns a copy of an object, NULL on failure.
 */
typedef void *(dup_func)(void const *const);

/**
 * delete_func - a function that deletes an object.
 */
typedef void(delete_func)(void *const);

/**
 * print_func - a function that prints an object.
 */
typedef int(print_func)(FILE *, void const *const);

/*singly linked list*/

typedef struct single_link_node single_link_node;

single_link_node *sln_new(void *const data, dup_func *duplicate_data);
single_link_node *sln_insert_after(
	single_link_node *const this_node, single_link_node *const ohter_node);
single_link_node *sln_insert_before(
	single_link_node *const this_node, single_link_node *other_node);
void *sln_remove(single_link_node *const node);
void *sln_get_data(single_link_node const *const node);
single_link_node *sln_get_next(single_link_node const *const node);
void sll_print(FILE *stream, single_link_node const *const head, print_func *print_data);
void *sll_clear(single_link_node *const head, delete_func *free_data);

/*doubly linked list*/

typedef struct double_link_node double_link_node;

double_link_node *dln_new(void *const data, dup_func *duplicate_data);
double_link_node *dln_insert_after(
	double_link_node *const this_node, double_link_node *const other_node);
double_link_node *dln_insert_before(
	double_link_node *const this_node, double_link_node *other_node);
void *dln_remove(double_link_node *node);
void *dln_get_data(double_link_node const *const node);
double_link_node *dln_get_next(double_link_node const *const node);
double_link_node *dln_get_previous(double_link_node const *const node);
void dll_print(FILE *stream, double_link_node const *const head, print_func *print_data);
void *dll_clear(double_link_node *const head, delete_func *free_data);

#endif /* LINKED_NODES_H */
