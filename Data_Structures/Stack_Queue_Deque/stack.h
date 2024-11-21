#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_lists.h"

/**
 * struct stack - a stack data structure.
 * @size: the number of nodes in the stack.
 * @top: pointer to the top of the stack.
 */
typedef struct stack
{
	size_t size;
	single_link_nd *top;
} stack;

single_link_nd *push(stack *s, void *data);
void *pop(stack *s);
void clear_stack(stack *s, void (*free_data)(void *));
void print_stack(stack *s, void (*print_data)(void *));

#endif /* STACK_H */
