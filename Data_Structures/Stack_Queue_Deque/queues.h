#ifndef QUEUES_H
#define QUEUES_H

#include <stddef.h> /* size_t */
#include <stdio.h>	/* printf */
#include <stdlib.h> /* *alloc */

#include "linked_lists.h"

typedef void *(dup_func)(void *);
typedef void(delete_func)(void *);
typedef int(print_func)(void *);

/*queue*/

typedef struct queue queue;

void *queue_delete(queue *const nullable_ptr, delete_func *free_data);
void *dequeue(queue * const q);
double_link_node *enqueue(
	queue *const q, void *const data, dup_func *copy_data);
queue *queue_new(void);
void queue_print(const queue *q, print_func *print_data);
queue *queue_from_array(
	void *const data_array, const size_t len,
	dup_func *copy_data, delete_func *delete_data);
size_t queue_len(queue *q);

/*deque*/

typedef struct deque deque;

double_link_node *push_head(deque *dq, void *data);
double_link_node *push_tail(deque *dq, void *data);
void *pop_head(deque *dq);
void *pop_tail(deque *dq);
void clear_deque(deque *dq, delete_func *free_data);
void print_deque(deque *dq, print_func *print_data);

#endif /* QUEUES_H */
