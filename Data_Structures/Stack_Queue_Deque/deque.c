#include "linked_lists.h"
#include "queues.h"

/**
 * struct deque - a queue data structure.
 * @size: number items in the queue.
 * @head: a pointer to the head of the queue.
 * @tail: a pointer to the tail of the queue.
 */
struct deque
{
	size_t size;
	struct double_link_node *head;
	struct double_link_node *tail;
};

/**
 * push_head - push an item to the head of the deque.
 * @dq: the deque to operate on.
 * @data: the data that the node will hold.
 *
 * Return: pointer to the newly added node, NULL if dq is NULL or failure.
 */
double_link_node *push_head(deque *dq, void *data)
{
	double_link_node *nw = NULL;

	if (!dq)
		return (NULL);

	nw = calloc(1, sizeof(*nw));
	if (!nw)
		return (NULL);

	nw->data = data;
	nw->next = dq->head;
	if (dq->head)
		dq->head->prev = nw;

	if (!dq->tail)
		dq->tail = nw;

	dq->head = nw;
	dq->size++;
	return (nw);
}

/**
 * push_tail - push an item to the tail of the deque.
 * @dq: the deque to operate on.
 * @data: the data that the node will hold.
 *
 * Return: pointer to the newly added node, NULL if dq is NULL or failure.
 */
double_link_node *push_tail(deque *dq, void *data)
{
	double_link_node *nw = NULL;

	if (!dq)
		return (NULL);

	nw = calloc(1, sizeof(*nw));
	if (!nw)
		return (NULL);

	nw->data = data;
	nw->prev = dq->tail;
	if (dq->tail)
		dq->tail->next = nw;

	if (!dq->head)
		dq->head = nw;

	dq->tail = nw;
	dq->size++;
	return (nw);
}

/**
 * pop_head - pops node at the head of the deque and returns its data.
 * @dq: the deque to operate on.
 *
 * Return: data that was in the popped node.
 */
void *pop_head(deque *dq)
{
	double_link_node *p = NULL;
	void *d = NULL;

	if (!dq || !dq->head)
		return (NULL);

	p = dq->head;
	d = dq->head->data;
	dq->head = dq->head->next;
	free(p);
	if (!dq->head)
		dq->tail = NULL;

	if (dq->size)
		dq->size--;

	return (d);
}

/**
 * pop_tail - pops node at the tail of the deque and returns its data.
 * @dq: the deque to operate on.
 *
 * Return: data that was in the popped node.
 */
void *pop_tail(deque *dq)
{
	double_link_node *p = NULL;
	void *d = NULL;

	if (!dq || !dq->tail)
		return (NULL);

	p = dq->tail;
	d = dq->tail->data;
	dq->tail = dq->tail->prev;
	free(p);
	if (!dq->tail)
		dq->head = NULL;

	if (dq->size)
		dq->size--;

	return (d);
}

/**
 * clear_deque - deletes a deque.
 * @dq: the deque to operate on.
 * @free_data: pointer to a function that will be called to free data in nodes.
 */
void clear_deque(deque *dq, void (*free_data)(void *))
{
	if (!dq || !dq->head)
		return;

	while (dq->head->next)
	{
		if (free_data)
			(*free_data)(dq->head->data);

		dq->head = dq->head->next;
		free(dq->head->prev);
	}

	if (free_data)
		(*free_data)(dq->head->data);

	free(dq->head);
	dq->head = NULL;
	dq->tail = NULL;
	dq->size = 0;
}

/**
 * print_deque - print all nodes of a deque.
 * @dq: the deque to print.
 * @print_data: function that will be called to print data in nodes.
 */
void print_deque(deque *dq, void (*print_data)(void *))
{
	double_link_node *walk = NULL;

	if (!dq)
		return;

	if (!dq->head)
		printf("(NULL)\n");

	if (print_data)
		(*print_data)(dq->head->data);
	else
		printf("%p", dq->head);

	walk = dq->head->next;
	while (walk)
	{
		if (print_data)
		{
			printf(" <=> ");
			(*print_data)(walk->data);
		}
		else
			printf(" <=> %p", walk->data);

		walk = walk->next;
	}

	printf("\n");
}
