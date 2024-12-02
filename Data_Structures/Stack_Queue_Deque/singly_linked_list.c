#include "linked_lists.h"

/**
 * struct single_link_node - a singly linked list node.
 * @data: data that the node holds.
 * @next: pointer to the next node.
 * @prev: pointer to the previous node.
 */
struct single_link_node
{
	void *data;
	struct single_link_node *next;
	struct single_link_node *prev;
};

/**
 * sln_new - allocates memory for a single link node and initialises it.
 * @data: the object to initialise with.
 * @duplicate_data: function that returns a separate copy of data,
 * if NULL a simple copy of the pointer to data is done.
 *
 * Return: pointer to the node, NULL on failure.
 */
single_link_node *sln_new(void *const data, dup_func *duplicate_data)
{
	single_link_node *new_node = calloc(1, sizeof(*new_node));

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
 * sln_insert_after - inserts a single link node after another.
 * @this_node: the node to insert after.
 * @other_node: the node to insert.
 *
 * Return: pointer to the newly inserted node.
 */
single_link_node *sln_insert_after(
	single_link_node *const this_node, single_link_node *const other_node)
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
 * sln_insert_before - insert a single link node before another.
 * @this_node: the node to insert before.
 * @other_node: the node to insert.
 *
 * Return: pointer to the newly inserted node.
 */
single_link_node *sln_insert_before(
	single_link_node *const this_node, single_link_node *other_node)
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
 * sln_remove - deletes a node and returns its data.
 * @node: the node to delete.
 *
 * Return: pointer to the data of the node.
 */
void *sln_remove(single_link_node *const node)
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
 * sln_get_data - return the data in a single link node.
 * @node: the node.
 *
 * Return: pointer to the data.
 */
void *sln_get_data(single_link_node const *const node)
{
	if (!node)
		return (NULL);

	return (node->data);
}

/**
 * sln_get_next - return a node's successor.
 * @node: the node to query.
 *
 * Return: pointer to the next node.
 */
single_link_node *sln_get_next(const single_link_node *node)
{
	if (!node)
		return (NULL);

	return (node->next);
}

/**
 * sll_print - print all nodes of a doubly linked list.
 * @stream: pointer to a stream to output to.
 * @head: head of the doubly linked list to print.
 * @print_data: function that will be called to print data in nodes.
 */
void sll_print(FILE *stream, single_link_node const *const head, print_func *print_data)
{
	if (!head)
		return;

	single_link_node const *walk = head;
	/*WARNING: need to check return values of printing functions.*/
	if (print_data)
		print_data(stream, sln_get_data(walk));
	else
		fprintf(stream, "%p", sln_get_data(walk));

	walk = sln_get_next(walk);
	while (walk)
	{
		printf(" --> ");
		if (print_data)
			print_data(stream, sln_get_data(walk));
		else
			fprintf(stream, "%p", sln_get_data(walk));

		walk = sln_get_next(walk);
	}

	fprintf(stream, "\n");
}

/**
 * sll_clear - delete a doubly linked list from memory.
 * @head: pointer to the head of the doubly linked list.
 * @free_data: function that will be called to free data in the nodes.
 *
 * Return: NULL always.
 */
void *sll_clear(single_link_node *const head, delete_func *free_data)
{
	if (!head)
		return (NULL);

	single_link_node *walk = head;
	void *data = NULL;

	while (walk->next)
	{
		walk = sln_get_next(walk);
		data = sln_remove(walk->prev);
		if (free_data)
			free_data(data);
	}

	data = sln_remove(walk);
	if (free_data)
		free_data(data);

	return (NULL);
}
