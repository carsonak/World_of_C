#ifndef QUEUES_H
#define QUEUES_H

#include <stddef.h> /* size_t */
#include <stdio.h>	/* *printf */
#include <stdlib.h> /* *alloc */

typedef void *(dup_func)(void const *const);
typedef void(delete_func)(void *const);
typedef int(print_func)(FILE *, void const *const);

typedef struct single_link_node single_link_node;
typedef struct double_link_node double_link_node;

/*queue*/

typedef struct queue queue;

void *queue_delete(queue *const nullable_ptr, delete_func *free_data);
void *dequeue(queue * const q);
double_link_node *enqueue(
	queue *const q, void *const data, dup_func *copy_data);
queue *queue_new(void);
void queue_print(FILE *stream, queue const *const q, print_func *print_data);
queue *queue_from_array(
	void *const data_array, const size_t len, const size_t type_size,
	dup_func *copy_data, delete_func *delete_data);
size_t queue_len(queue const *const q);

/*deque*/

typedef struct deque deque;

double_link_node *push_head(deque *const dq, void const *const data);
double_link_node *push_tail(deque *const dq, void const *const data);
void *pop_head(deque *const dq);
void *pop_tail(deque *const dq);
void clear_deque(deque *const dq, delete_func *free_data);
void print_deque(FILE *stream, deque const *const dq, print_func *print_data);

#endif /* QUEUES_H */
