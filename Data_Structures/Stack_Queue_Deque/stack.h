#ifndef STACK_H
#define STACK_H

#include <stddef.h> /* size_t */
#include <stdio.h>  /* *printf */
#include <stdlib.h> /* *alloc */

#include "typedefs.h"

stack *stk_new(void);
single_link_node *stk_push(
	stack *const s, void *const data, dup_func *copy_data);
void *stk_pop(stack *const s);
void stk_print(stack *const s, print_func *print_data);

#endif /* STACK_H */
