#include "linked_lists.h"

/**
 * struct double_link_node - a doubly linked list node.
 * @data: data that the node holds.
 * @next: pointer to the next node.
 * @prev: pointer to the previous node.
 */
struct double_link_node
{
	void *data;
	struct double_link_node *next;
	struct double_link_node *prev;
};

/**
 * dln_new - allocates memory for a double link node and initialises it.
 * @data: the object to initialise with.
 * @duplicate_data: function that returns a separate copy of data,
 * if NULL a simple copy of the pointer to data is done.
 *
 * Return: pointer to the node, NULL on failure.
 */
double_link_node *dln_new(void *const data, dup_func *duplicate_data)
{
	double_link_node *new_node = calloc(1, sizeof(*new_node));

	if (!new_node)
		return (NULL);

	new_node->data = data;
	if (duplicate_data)
	{
		new_node->data = duplicate_data(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}

	return (new_node);
}

/**
 * dln_insert_after - inserts a double link node after another.
 * @this_node: the node to insert after.
 * @other_node: the node to insert.
 *
 * Return: pointer to the newly inserted node.
 */
double_link_node *dln_insert_after(
	double_link_node *const this_node, double_link_node *const other_node)
{
	if (!this_node)
		return (other_node);

	if (!other_node)
		return (this_node);

	other_node->prev = this_node;
	other_node->next = this_node->next;
	if (this_node->next)
		this_node->next->prev = other_node;

	this_node->next = other_node;
	return (other_node);
}

/**
 * dln_insert_before - insert a double link node before another.
 * @this_node: the node to insert before.
 * @other_node: the node to insert.
 *
 * Return: pointer to the newly inserted node.
 */
double_link_node *dln_insert_before(
	double_link_node *const this_node, double_link_node *other_node)
{
	if (!this_node)
		return (other_node);

	if (!other_node)
		return (this_node);

	other_node->next = this_node;
	other_node->prev = this_node->prev;
	if (this_node->prev)
		this_node->prev->next = other_node;

	this_node->prev = other_node;
	return (other_node);
}

/**
 * dln_remove - deletes a node and returns its data.
 * @node: the node to delete.
 *
 * Return: pointer to the data of the node.
 */
void *dln_remove(double_link_node *const node)
{
	void *d = NULL;

	if (!node)
		return (NULL);

	d = node->data;
	node->data = NULL;
	if (node->next)
		node->next->prev = node->prev;

	if (node->prev)
		node->prev->next = node->next;

	node->next = NULL;
	node->prev = NULL;
	free(node);
	return (d);
}

/**
 * dln_get_data - return the data in a double link node.
 * @node: the node.
 *
 * Return: pointer to the data.
 */
void *dln_get_data(double_link_node const *const node)
{
	if (!node)
		return (NULL);

	return (node->data);
}

/**
 * dln_get_next - return a node's successor.
 * @node: the node to query.
 *
 * Return: pointer to the next node.
 */
double_link_node *dln_get_next(double_link_node const *const node)
{
	if (!node)
		return (NULL);

	return (node->next);
}

/**
 * dln_get_previous - return a node's predecessor.
 * @node: the node to query.
 *
 * Return: pointer to the previous node.
 */
double_link_node *dln_get_previous(double_link_node const *const node)
{
	if (!node)
		return (NULL);

	return (node->prev);
}

/**
 * dll_print - print all nodes of a doubly linked list.
 * @stream: pointer to a stream to output to.
 * @head: head of the doubly linked list to print.
 * @print_data: function that will be called to print data in nodes.
 */
void dll_print(FILE *stream, double_link_node const *const head, print_func *print_data)
{
	if (!head)
		return;

	double_link_node const *walk = head;
	/*WARNING: need to check return values of printing functions.*/
	if (print_data)
		print_data(stream, dln_get_data(walk));
	else
		fprintf(stream, "%p", dln_get_data(walk));

	walk = dln_get_next(walk);
	while (walk)
	{
		printf(" <--> ");
		if (print_data)
			print_data(stream, dln_get_data(walk));
		else
			fprintf(stream, "%p", dln_get_data(walk));

		walk = dln_get_next(walk);
	}

	fprintf(stream, "\n");
}

/**
 * dll_print_reversed - print all nodes of a deque from tail to head.
 * @stream: pointer to the stream to output to.
 * @dll: the deque to print.
 * @print_data: function that will be called to print data in nodes.
 */
void dll_print_reversed(
	FILE *stream, double_link_node const *const head, print_func *print_data)
{
	if (!head)
		return;

	double_link_node const *walk = head;
	/*WARNING: need to check return values of the printing functions.*/
	if (print_data)
		print_data(stream, dln_get_data(walk));
	else
		fprintf(stream, "%p", dln_get_data(walk));

	walk = dln_get_previous(walk);
	while (walk)
	{
		fprintf(stream, " <--> ");
		void *d = dln_get_data(walk);

		if (print_data)
			print_data(stream, d);
		else
			fprintf(stream, "%p", d);

		walk = dln_get_previous(walk);
	}

	fprintf(stream, "\n");
}

/**
 * dll_delete - delete a doubly linked list from memory.
 * @head: pointer to the head of the doubly linked list.
 * @free_data: function that will be called to free data in the nodes.
 *
 * Return: NULL always.
 */
void *dll_delete(double_link_node *const head, delete_func *free_data)
{
	if (!head)
		return (NULL);

	double_link_node *walk = head;
	void *data = NULL;

	while (walk->next)
	{
		walk = dln_get_next(walk);
		data = dln_remove(walk->prev);
		if (free_data)
			free_data(data);
	}

	data = dln_remove(walk);
	if (free_data)
		free_data(data);

	return (NULL);
}
