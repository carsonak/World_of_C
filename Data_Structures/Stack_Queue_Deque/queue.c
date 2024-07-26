#include "queue.h"

/**
 * enqueue - add an item to the end of a queue.
 * @q: the queue to operate on.
 * @data: data that the node will store.
 *
 * Return: pointer to the newly added node, NULL if q is NULL or failure.
 */
double_link_nd *enqueue(queue *q, void *data)
{
	double_link_nd *nw = NULL;

	if (!q)
		return (NULL);

	nw = calloc(1, sizeof(*nw));
	if (!nw)
		return (NULL);

	nw->data = data;
	nw->prev = q->tail;
	if (q->tail)
		q->tail->next = nw;

	if (!q->head)
		q->head = nw;

	q->tail = nw;
	q->size++;
	return (nw);
}

/**
 * dequeue - pop an item from the start of a queue and return its data.
 * @q: the queue to operate on.
 *
 * Return: pointer to the data in the popped node, NULL if q or head is NULL.
 */
void *dequeue(queue *q)
{
	double_link_nd *p = NULL;
	void *d = NULL;

	if (!q || !q->head)
		return (NULL);

	p = q->head;
	d = q->head->data;
	q->head = q->head->next;
	free(p);
	if (!q->head)
		q->tail = NULL;

	if (q->size)
		q->size--;

	return (d);
}

/**
 * clear_queue - delete a queue.
 * @q: the queue to operate on.
 * @free_data: pointer to a function that will be called to free data in nodes.
 */
void clear_queue(queue *q, void (*free_data)(void *))
{
	if (!q || !q->head)
		return;

	while (q->head->next)
	{
		if (free_data)
			(*free_data)(q->head->data);

		q->head = q->head->next;
		free(q->head->prev);
	}

	if (free_data)
		(*free_data)(q->head->data);

	free(q->head);
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
}

/**
 * print_queue - print all nodes of a queue.
 * @q: the queue to print.
 * @print_data: function that will be called to print data in nodes.
 */
void print_queue(queue *q, void (*print_data)(void *))
{
	double_link_nd *walk = NULL;

	if (!q)
		return;

	if (!q->head)
		printf("(NULL)\n");

	if (print_data)
		(*print_data)(q->head->data);
	else
		printf("%p", q->head);

	walk = q->head->next;
	while (walk)
	{
		if (print_data)
		{
			printf(" --> ");
			(*print_data)(walk->data);
		}
		else
			printf(" --> %p", walk->data);

		walk = walk->next;
	}

	printf("\n");
}
