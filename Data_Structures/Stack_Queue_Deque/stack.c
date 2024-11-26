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
 * push - push an item onto a.
 * @s: the stack to operate on.
 * @data: data that will be stored in the node.
 *
 * Return: pointer to the newly added node, NULL if s is NULL or failure.
 */
single_link_nd *push(stack *s, void *data)
{
	single_link_nd *nw = NULL;

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
	single_link_nd *n = NULL;
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
void clear_stack(stack *s, void (*free_data)(void *))
{
	single_link_nd *p = NULL;

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
 * @s: the stack to print.
 * @print_data: function that will be called to print data in nodes.
 */
void print_stack(stack *s, void (*print_data)(void *))
{
	double_link_node *walk = NULL;

	if (!s)
		return;

	if (!s->top)
	{
		printf("(NULL)\n");
		return;
	}

	walk = s->top;
	while (walk)
	{
		printf("+");
		if (print_data)
			(*print_data)(walk->data);
		else
			printf("%p", walk->data);

		printf("\n++++++++++++\n");
		walk = walk->next;
	}
}
