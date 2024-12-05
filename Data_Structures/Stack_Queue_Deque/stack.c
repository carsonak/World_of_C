#include "linked_lists.h"
#include "stack.h"

/**
 * struct stack - a stack data structure.
 * @len: the number of nodes in the stack.
 * @top: pointer to the top of the stack.
 */
struct stack
{
	size_t len;
	single_link_node *top;
};

/**
 * stk_new - allocates space for an empty stack.
 *
 * Return: pointer to the new stack, NULL on failure.
 */
stack *stk_new(void) { return (calloc(1, sizeof(stack))); }

/**
 * stk_len - return number of nodes in the stack.
 * @s: the stack to operate on.
 *
 * Return: number of nodes in the stack.
 */
size_t stk_len(stack const *const s)
{
	if (!s)
		return (0);

	return (s->len);
}

/**
 * stk_peek - return data at the top of the stack without deleting the node.
 * @s: the stack to operate on.
 *
 * Return: pointer to data at the top of the stack.
 */
void *stk_peek(stack const *const s)
{
	if (!s)
		return (NULL);

	return (sln_get_data(s->top));
}

/**
 * stk_push - push an item onto a.
 * @s: the stack to operate on.
 * @data: data that will be stored in the node.
 * @copy_data: function that will be used to duplicate the data.
 *
 * Return: pointer to the newly added node, NULL if s is NULL or failure.
 */
single_link_node *stk_push(
	stack *const s, void *const data, dup_func *copy_data)
{
	if (!s)
		return (NULL);

	single_link_node *new_top = sln_new(data, copy_data);

	if (!new_top)
		return (NULL);

	s->top = sln_insert_before(s->top, new_top);
	++(s->len);
	return (new_top);
}

/**
 * stk_pop - pop the top node on the stack and returns the data.
 * @s: the stack to operate on.
 *
 * Return: pointer to the data that was in the top node, NULL if s is NULL.
 */
void *stk_pop(stack *const s)
{
	if (!s || !s->top)
		return (NULL);

	single_link_node *old_top = s->top;

	s->top = sln_get_next(old_top);
	void *data = sln_remove(old_top);

	if (s->len)
		--(s->len);

	return (data);
}

/**
 * clear_stack - delete a stack.
 * @s: the stack to operate on.
 * @free_data: pointer to a function that will be called to free data in nodes.
 */
static void clear_stack(stack *const s, delete_func *free_data)
{
	single_link_node *next_node = NULL;
	void *d = NULL;

	if (!s || !s->top)
		return;

	next_node = sln_get_next(s->top);
	while (next_node)
	{
		d = sln_remove(s->top);
		if (free_data)
			free_data(d);

		s->top = next_node;
		next_node = sln_get_next(s->top);
	}

	d = sln_remove(s->top);
	if (free_data)
		free_data(d);

	s->top = NULL;
	s->len = 0;
}

/**
 * stk_delete - delete a stack.
 * @nullable_ptr: pointer to the stack to delete.
 * @free_data: pointer to a function that can free data in the queue.
 *
 * Return: NULL always.
 */
void *stk_delete(stack *const nullable_ptr, delete_func *free_data)
{
	clear_stack(nullable_ptr, free_data);
	free(nullable_ptr);
	return (NULL);
}

/**
 * stk_print - print all nodes of a stack.
 * @stream: pointer to stream to write to.
 * @s: the stack to print.
 * @print_data: function that will be called to print data in nodes.
 */
void stk_print(FILE *stream, stack const *const s, print_func *print_data)
{
	single_link_node *walk = NULL;

	if (!s)
		return;

	if (!s->top)
	{
		fprintf(stream, "(NULL)\n");
		return;
	}

	walk = s->top;
	while (walk)
	{
		fprintf(stream, "+ ");
		void *d = sln_get_data(walk);

		if (print_data)
			print_data(stream, d);
		else
			fprintf(stream, "%p", d);

		fprintf(stream, "\n++++++++++++\n");
		walk = sln_get_next(walk);
	}
}
