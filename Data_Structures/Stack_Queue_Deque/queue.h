#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_lists.h"

/**
 * struct queue - a queue data structure.
 * @size: number items in the queue.
 * @head: a pointer to the head of the queue.
 * @tail: a pointer to the tail of the queue.
 */
struct queue
{
	size_t size;
	double_link_nd *head;
	double_link_nd *tail;
};

typedef struct queue queue;
typedef struct queue deque;

/*queue*/

double_link_nd *enqueue(queue *q, void *data);
void *dequeue(queue *q);
void clear_queue(queue *q, void (*free_data)(void *));
void print_queue(queue *q, void (*print_data)(void *));

/*deque*/

double_link_nd *push_head(deque *dq, void *data);
double_link_nd *push_tail(deque *dq, void *data);
void *pop_head(deque *dq);
void *pop_tail(deque *dq);
void clear_deque(deque *dq, void (*free_data)(void *));
void print_deque(deque *dq, void (*print_data)(void *));

#endif /* QUEUE_H */
