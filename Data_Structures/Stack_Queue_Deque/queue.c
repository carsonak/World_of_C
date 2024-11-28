#include "queues.h"

/**
 * struct queue - a queue data structure.
 * @size: number items in the queue.
 * @head: a pointer to the head of the queue.
 * @tail: a pointer to the tail of the queue.
 */
struct queue
{
	size_t size;
	double_link_node *head;
	double_link_node *tail;
};

/**
 * queue_new - allocate memory for an empty queue.
 *
 * Return: pointer to the new queue, NULL on failure.
 */
queue *queue_new(void) { return (calloc(1, sizeof(queue))); }

/**
 * queue_len - return total items in the queue.
 * @q: pointer to the queue.
 *
 * Return: total items in the queue.
 */
size_t queue_len(queue *q)
{
	if (!q)
		return (0);

	return (q->size);
}

/**
 * enqueue - add an item to the end of a queue.
 * @q: the queue to operate on.
 * @data: data that the node will store.
 * @duplicate_data: function that returns a separate copy of data,
 * if NULL a simple copy of the pointer to data is done.
 *
 * Return: pointer to the newly added node, NULL if q is NULL or failure.
 */
double_link_node *enqueue(
	queue *const q, void *const data, dup_func *duplicate_data)
{
	double_link_node *nw = NULL;

	if (!q)
		return (NULL);

	nw = dln_new(data, duplicate_data);
	if (!nw)
		return (NULL);

	q->tail = dln_insert_after(q->tail, nw);
	if (!q->head)
		q->head = nw;

	q->size++;
	return (nw);
}

/**
 * dequeue - pop an item from the start of a queue and return its data.
 * @q: the queue to operate on.
 *
 * Return: pointer to the data in the popped node, NULL if q or head is NULL.
 */
void *dequeue(queue *const q)
{
	double_link_node *node = NULL;
	void *d = NULL;

	if (!q || !q->head)
		return (NULL);

	node = q->head;
	q->head = dln_get_next(node);
	d = dln_remove(node);
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
static void clear_queue(queue *const q, delete_func *free_data)
{
	double_link_node *next_node = NULL;

	if (!q || !q->head)
		return;

	next_node = dln_get_next(q->head);
	while (next_node)
	{
		if (free_data)
			free_data(dln_remove(q->head));

		q->head = next_node;
		next_node = dln_get_next(q->head);
	}

	if (free_data)
		free_data(dln_remove(q->head));

	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
}

/**
 * queue_delete - frees a queue from memory.
 * @nullable_ptr: pointer to the queue to delete.
 * @free_data: pointer to a function that can free data in the queue.
 *
 * Return: NULL always.
 */
void *queue_delete(queue *const nullable_ptr, delete_func *free_data)
{
	clear_queue(nullable_ptr, free_data);
	free(nullable_ptr);
	return (NULL);
}

/**
 * queue_from_array - create a new queue from an array of objects.
 * @data_array: the array of objects.
 * @len: the size of the array.
 * @duplicate_data: function that will be used to copy the objects.
 * @delete_data: function that will be used to delete objects on failure.
 *
 * Return: pointer to the new queue, NULL on failure.
 */
queue *queue_from_array(
	void *const data_array, const size_t len,
	dup_func *duplicate_data, delete_func *delete_data)
{
	queue *new_q = NULL;

	if (!data_array || len == 0)
		return (NULL);

	if (duplicate_data && !delete_data)
		return (NULL);

	new_q = queue_new();
	if (!new_q)
		return (NULL);

	for (size_t i = 0; i < len; i++)
	{
		void *data = data_array + (sizeof(*data) * i);

		if (duplicate_data)
			data = duplicate_data(data);

		if (!data || !enqueue(new_q, data, duplicate_data))
		{
			new_q = queue_delete(new_q, delete_data);
			break;
		}
	}

	return (new_q);
}

/**
 * queue_print - print all nodes of a queue.
 * @q: the queue to print.
 * @print_data: function that will be called to print data in nodes.
 */
void queue_print(const queue *q, print_func *print_data)
{
	double_link_node const *walk = NULL;

	if (!q)
		return;

	if (!q->head)
	{
		printf("(NULL)\n");
		return;
	}

	walk = q->head;
	if (print_data)
		print_data(dln_get_data(walk));
	else
		printf("%p", dln_get_data(walk));

	walk = dln_get_next(walk);
	while (walk)
	{
		printf(" --> ");
		if (print_data)
			print_data(dln_get_data(walk));
		else
			printf("%p", dln_get_data(walk));

		walk = dln_get_next(walk);
	}

	printf("\n");
}
