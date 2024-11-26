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
 * @copy_data: function that returns a separate copy of data,
 * if NULL a simple copy of the pointer to data is done.
 *
 * Return: pointer to the node, NULL on failure.
 */
single_link_node *sln_new(void *const data, copy_func *copy_data)
{
	single_link_node *new_node = calloc(1, sizeof(*new_node));

	if (!new_node)
		return (NULL);

	new_node->data = data;
	if (copy_data)
	{
		new_node->data = copy_data(data);
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
 * @node: the node to insert.
 *
 * Return: pointer to the newly inserted node.
 */
single_link_node *sln_insert_after(
	single_link_node *const node, single_link_node *const this_node)
{
	if (!this_node)
		return (node);

	if (!node)
		return (this_node);

	node->prev = this_node;
	node->next = this_node->next;
	if (this_node->next)
		this_node->next->prev = node;

	this_node->next = node;
	return (node);
}

/**
 * sln_remove - deletes a node and returns its data.
 * @node: the node to delete.
 *
 * Return: pointer to the data of the node.
 */
void *sln_remove(single_link_node *node)
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
void *sln_get_data(const single_link_node *node)
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
