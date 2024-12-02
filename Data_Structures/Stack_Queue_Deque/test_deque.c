#include "queues.h"

/**
 * print_llint - prints an int.
 * @d: pointer to the int.
 *
 * Return: same as printf.
 */
static int print_llint(FILE *stream, long long int const *const d)
{
	if (!d)
		return (fprintf(stream, "NULL"));

	return (fprintf(stream, "%lld", *d));
}

/**
 * dup_llint - make a copy of an int pointer.
 * @n: pointer to the int.
 *
 * Return: pointer to a new int.
 */
static long long int *dup_llint(long long int const *const n)
{
	long long int *const ptr = calloc(1, sizeof(*ptr));

	if (n && ptr)
		*ptr = *n;

	return (ptr);
}

/**
 * print_char - prints a char.
 * @stream: stream to print out to.
 * @c: pointer to the char.
 *
 * Return: same as printf.
 */
static int print_char(FILE *stream, char const *const c)
{
	if (!c)
		return (fprintf(stream, "NULL"));

	return (fprintf(stream, "%c", *c));
}

/**
 * dup_char - make a copy of an char pointer.
 * @c: pointer to the char.
 *
 * Return: pointer to a new char.
 */
static char *dup_char(char const *const c)
{
	char *const ptr = calloc(1, sizeof(*ptr));

	if (c && ptr)
		*ptr = *c;

	return (ptr);
}

/**
 * create_llint_array - create an int array and initialise with a range of values.
 * @len: length of the array to create.
 * @start: starting value.
 * @step: size between each value.
 *
 * Return: pointer to the array, NULL on failure.
 */
static long long int *create_llint_array(const size_t len, const long long int start, const long long int step)
{
	long long int c = start;
	long long int *new_arr = malloc(len * sizeof(*new_arr));

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
 * main - tests for deque.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{
	const size_t arr_len = 32;
	long long int *arr = create_llint_array(arr_len, 1, 1);
	deque *my_q = dq_from_array(
		(void *)arr, arr_len, sizeof(*arr), (dup_func *)dup_llint, free);

	free(arr);
	dq_print(stdout, my_q, (print_func *)print_llint);
	putchar('\n');

	dq_push_tail(my_q, malloc(sizeof(*arr)), NULL);
	dq_print(stdout, my_q, (print_func *)print_llint);
	putchar('\n');

	free(dq_pop_tail(my_q));
	dq_push_head(my_q, malloc(sizeof(*arr)), NULL);
	dq_print_reversed(stdout, my_q, (print_func *)print_llint);
	putchar('\n');

	free(dq_pop_head(my_q));
	dq_print(stdout, my_q, (print_func *)print_llint);
	putchar('\n');

	my_q = dq_delete(my_q, free);
	char s[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!";

	my_q = dq_from_array(s, sizeof(s) - 1, sizeof(*s), (dup_func *)dup_char, free);
	dq_print(stdout, my_q, (print_func *)print_char);
	dq_print_reversed(stdout, my_q, (print_func *)print_char);
	putchar('\n');

	my_q = dq_delete(my_q, free);
	return (0);
}
