#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct single_link_node single_link_node;
typedef struct stack stack;

single_link_node *push(stack *s, void *data);
void *pop(stack *s);
void clear_stack(stack *s, void (*free_data)(void *));
void print_stack(stack *s, void (*print_data)(void *));

#endif /* STACK_H */
