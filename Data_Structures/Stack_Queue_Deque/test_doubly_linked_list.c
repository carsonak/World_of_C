#include "linked_lists.h"
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>

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
 * isvowel - checks if a character is a vowel.
 * @c: the character to check.
 *
 * Return: true if the character is a vowel.
 */
static bool isvowel(const char c)
{
	const char lc = tolower(c);

	return (lc == 'a' || lc == 'e' || lc == 'i' || lc == 'o' || lc == 'u');
}

/**
 * filter_vowels_and_digits - filter vowels and digits from a linked list inplace.
 * @head: pointer to the head of the list.
 *
 * Return: pointer to the new head.
 */
static double_link_node *filter_vowels_and_digits(double_link_node *head)
{
	double_link_node *walk = head;

	while (dln_get_next(walk))
	{
		walk = dln_get_next(walk);
		char c = *((char *)dln_get_data(dln_get_previous(walk)));

		if (!isdigit(c) && !isvowel(c))
		{
			double_link_node *prev = dln_get_previous(walk);

			if (prev == head)
				head = walk;

			dln_remove(prev);
		}
	}

	if (!isdigit(*((char *)dln_get_data(walk))) || !isvowel(*((char *)dln_get_data(walk))))
	{
		if (head == walk)
			head = NULL;

		dln_remove(walk);
	}

	return (head);
}

/**
 * main - tests for doubly linked list.
 *
 * Return: 0.
 */
int main(void)
{
	double_link_node *head = NULL, *walk = NULL;
	char s[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\" #$ % &'()*+,-./:;<=>?@[\\]^_`{|}~";

	head = dln_new(s, NULL);
	walk = head;
	for (size_t i = 1; i < (sizeof(s) / sizeof(*s)) - 1; i++)
		walk = dln_insert_after(walk, dln_new(s + i, NULL));

	dll_print(stdout, head, (print_func *)print_char);
	putchar('\n');

	head = filter_vowels_and_digits(head);
	dll_print(stdout, head, (print_func *)print_char);
	putchar('\n');

	head = dll_delete(head, NULL);
	const size_t arr_len = 64;
	long long int *arr = create_llint_array(arr_len, -9000000000000000000, 4205000000);

	head = dln_new(arr, (dup_func *)dup_llint);
	walk = head;
	for (size_t i = 1; i < arr_len; i++)
		walk = dln_insert_after(walk, dln_new(&arr[i], (dup_func *)dup_llint));

	dll_print(stdout, head, (print_func *)print_llint);
	free(arr);
	head = dll_delete(head, free);
	return (0);
}
