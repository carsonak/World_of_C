#include "queues.h"

/**
 * print_int - prints an int.
 * @d: pointer to the int.
 *
 * Return: same as printf.
 */
static int print_int(int *d)
{
	if (!d)
		return (printf("NULL"));

	return (printf("%d", *d));
}

/**
 * dup_int - make a copy of an int pointer.
 * @n: pointer to the int.
 *
 * Return: pointer to a new int.
 */
static int *dup_int(const int *n)
{
	int *const ptr = calloc(1, sizeof(*ptr));

	if (n && ptr)
		*ptr = *n;

	return (ptr);
}

/**
 * create_int_array - create an int array and initialise with a range of values.
 * @len: length of the array to create.
 * @start: starting value.
 * @step: size between each value.
 *
 * Return: pointer to the array, NULL on failure.
 */
static int *create_int_array(const size_t len, const int start, const int step)
{
	int c = start;
	int *new_arr = malloc(len * sizeof(*new_arr));

	if (!new_arr)
		return (NULL);

	for (size_t i = 0; i < len; i++)
	{
		new_arr[i] = c;
		c += step;
	}

	return (new_arr);
}

/**
 * main - tests for queue.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{
	const size_t arr_len = 64;
	int *arr = create_int_array(arr_len, 1, 1);
	queue *my_q = queue_from_array((void *)arr, arr_len, (void *(*)(void *))dup_int, free);

	free(arr);
	queue_print(my_q, (int (*)(void *))print_int);
	putchar('\n');

	enqueue(my_q, malloc(sizeof(*arr)), NULL);
	queue_print(my_q, (int (*)(void *))print_int);
	putchar('\n');

	my_q = queue_delete(my_q, free);

	return (0);
}
