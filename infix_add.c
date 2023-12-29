#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

char *infiX_add(char *n1, char *n2);
size_t pad_char(char *str, char *ch);

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: pointer to an array of strings
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	uint8_t *rem = calloc(100, sizeof(*rem));

	if (argc != 3)
	{
		fprintf(stderr, "USAGE: %s <num1> <num2>", argv[0]);
		return (EXIT_FAILURE);
	}
	else if (!isdigit(argv[1][0]) || !isdigit(argv[2][0]))
	{
		fprintf(stderr, "Insufficient digits to add");
		return (EXIT_FAILURE);
	}

	printf("%s - %s = %s\n", argv[1], argv[2], infiX_add((uint8_t *)argv[1], (uint8_t *)argv[2]));
	return (EXIT_SUCCESS);
}

/**
 * infiX_add - adds numbers stored in strings.
 * @n1: the first string with only decimals.
 * @n2: the second string with only decimals.
 *
 * Return: pointer to result, NULL on malloc fail or if both strings are empty
 */
char *infiX_add(char *n1, char *n2)
{
	ssize_t a = 0, b = 0, byt_sum = 0, sum_i = 0;
	char *sum = NULL;

	n1 += n1 ? pad_char(n1, "0") : 0;
	n2 += n2 ? pad_char(n2, "0") : 0;
	a = n1 ? (ssize_t)(strlen(n1) - 1) : -1;
	b = n2 ? (ssize_t)(strlen(n2) - 1) : -1;
	sum_i = (a > b) ? a : b;
	if (sum_i < 0)
		return (NULL);

	sum = malloc(sizeof(*sum) * ((++sum_i) + 2));
	if (!sum)
		return (NULL);

	sum[sum_i + 1] = '\0';
	sum[0] = '0';
	while (a >= 0 || b >= 0 || byt_sum > 0)
	{
		if (a >= 0)
		{
			byt_sum += (n1[a] - '0');
			--a;
		}

		if (b >= 0)
		{
			byt_sum += (n2[b] - '0');
			--b;
		}

		sum[sum_i] = (byt_sum % 10) + '0';
		byt_sum /= 10;
		--sum_i;
	}

	return (sum);
}

/**
 * pad_char - calculates length of initial padding characters in a string
 * @str: the string to check
 * @ch: the character
 *
 * Return: number of padding characters
 */
size_t pad_char(char *str, char *ch)
{
	size_t zeros = 0, len = 0;

	if (str)
	{
		len = strlen(str);
		zeros = strspn(str, ch);
		if (len && (zeros == len))
			zeros--;
	}

	return (zeros);
}
