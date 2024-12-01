#ifndef STACK_H
#define STACK_H

#include <stddef.h> /* size_t */
#include <stdio.h>  /* *printf */
#include <stdlib.h> /* *alloc */

typedef void *(dup_func)(void const *const);
typedef void(delete_func)(void *const);
typedef int(print_func)(FILE *, void const *const);

typedef struct single_link_node single_link_node;
typedef struct stack stack;

stack *stk_new(void);
single_link_node *push(stack *const s, void *const data);
void *pop(stack *const s);
void clear_stack(stack *const s, delete_func *free_data);
void print_stack(stack *const s, print_func *print_data);

#endif /* STACK_H */
