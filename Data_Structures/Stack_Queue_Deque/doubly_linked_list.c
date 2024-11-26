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
 * @copy_data: function that returns a separate copy of data,
 * if NULL a simple copy of the pointer to data is done.
 *
 * Return: pointer to the node, NULL on failure.
 */
double_link_node *dln_new(void *const data, copy_func *copy_data)
{
	double_link_node *new_node = calloc(1, sizeof(*new_node));

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
 * dln_insert_after - inserts a double link node after another.
 * @this_node: the node to insert after.
 * @node: the node to insert.
 *
 * Return: pointer to the newly inserted node.
 */
double_link_node *dln_insert_after(
	double_link_node *const this_node, double_link_node *const node)
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
 * dln_remove - deletes a node and returns its data.
 * @node: the node to delete.
 *
 * Return: pointer to the data of the node.
 */
void *dln_remove(double_link_node *node)
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
void *dln_get_data(const double_link_node *node)
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
double_link_node *dln_get_next(const double_link_node *node)
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
double_link_node *dln_get_previous(const double_link_node *node)
{
	if (!node)
		return (NULL);

	return (node->prev);
}
