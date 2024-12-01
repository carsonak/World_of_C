#include "linked_lists.h"
#include "stack.h"

/**
 * struct stack - a stack data structure.
 * @size: the number of nodes in the stack.
 * @top: pointer to the top of the stack.
 */
struct stack
{
	size_t size;
	single_link_node *top;
};

/**
 * stk_new - allocates space for an empty stack.
 *
 * Return: pointer to the new stack, NULL on failure.
 */
stack *stk_new(void) { return (calloc(1, sizeof(stack))); }

/**
 * push - push an item onto a.
 * @s: the stack to operate on.
 * @data: data that will be stored in the node.
 *
 * Return: pointer to the newly added node, NULL if s is NULL or failure.
 */
single_link_node *push(stack *s, void *data)
{
	single_link_node *nw = NULL;

	if (!s)
		return (NULL);

	nw = calloc(1, sizeof(*nw));
	if (!nw)
		return (NULL);

	nw->data = data;
	nw->next = s->top;
	s->top = nw;
	s->size++;
	return (nw);
}

/**
 * pop - pop the top node on the stack and returns the data.
 * @s: the stack to operate on.
 *
 * Return: pointer to the data that was in the top node, NULL if s is NULL.
 */
void *pop(stack *s)
{
	single_link_node *n = NULL;
	void *data = NULL;

	if (!s || !s->top)
		return (NULL);

	data = s->top->data;
	n = s->top;
	s->top = s->top->next;
	if (s->size)
		s--;

	free(n);
	return (data);
}

/**
 * clear_stack - delete a stack.
 * @s: the stack to operate on.
 * @free_data: pointer to a function that will be called to free data in nodes.
 */
void clear_stack(stack *s, delete_func *free_data)
{
	single_link_node *p = NULL;

	if (!s)
		return;

	while (s->top)
	{
		p = s->top;
		s->top = s->top->next;
		if (free_data)
			free_data(p->data);

		free(p);
	}

	s->size = 0;
}

/**
 * print_stack - print all nodes of a stack.
 * @stream: pointer to stream to write to.
 * @s: the stack to print.
 * @print_data: function that will be called to print data in nodes.
 */
void print_stack(FILE *stream, stack const *const s, print_func *print_data)
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
		printf("+");
		if (print_data)
			print_data(stream, walk->data);
		else
			fprintf(stream, "%p", walk->data);

		fprintf(stream, "\n++++++++++++\n");
		walk = walk->next;
	}
}
