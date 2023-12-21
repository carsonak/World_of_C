#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int only_digits(char *str);

/**
 * main - sieve of atkins
 * @argc: number of arguments
 * @argv: array with the argument strings
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{

	long limit = 0, wlimit = 0;
	ssize_t i, j, count, x, y, z;
	unsigned char *sieb = NULL;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	if (!only_digits(argv[1]))
	{
		fprintf(stderr, "Only decimals allowed\n");
		return (EXIT_FAILURE);
	}

	limit = strtol(argv[1], NULL, 10);
	sieb = calloc(limit, sizeof(*sieb));
	if (!sieb)
	{
		fprintf(stderr, "A memory error occured\n");
		return (EXIT_FAILURE);
	}

	wlimit = sqrt(limit);
	for (x = 1; x <= wlimit; x++)
	{
		for (y = 1; y <= wlimit; y++)
		{
			z = (4 * x * x) + (y * y);

			if (z <= limit &&
				(z % 60 == 1 || z % 60 == 13 || z % 60 == 17 || z % 60 == 29 ||
				 z % 60 == 37 || z % 60 == 41 || z % 60 == 49 || z % 60 == 53))
				sieb[z] = !sieb[z];

			z = (3 * x * x) + (y * y);

			if (z <= limit &&
				(z % 60 == 7 || z % 60 == 19 || z % 60 == 31 || z % 60 == 43))
				sieb[z] = !sieb[z];

			z = (3 * x * x) - (y * y);

			if (x > y && z <= limit &&
				(z % 60 == 11 || z % 60 == 23 || z % 60 == 47 || z % 60 == 59))
				sieb[z] = !sieb[z];
		}
	}

	for (i = 5; i <= wlimit; i++)
		if (sieb[i] == 1)
			for (j = 1; j * i * i <= limit; j++)
				sieb[j * i * i] = 0;

	printf("Primes in range %ld:\n%4d %4d %4d ", limit, 2, 3, 5);
	for (i = 5, count = 3; i <= limit; i++)
	{
		if (sieb[i] == 1)
		{
			printf("%5ld ", i);
			if (!(++count % 16))
				putchar('\n');
		}
	}

	putchar('\n');
	free(sieb);
	return (EXIT_SUCCESS);
}

/**
 * only_digits - checks for non-digits in a string
 * @str: the string
 *
 * Return: 1 if string is only digits, else 0
 */
int only_digits(char *str)
{
	size_t i, len = strlen(str);

	for (i = 0; i < len; i++)
		if (!isdigit(str[i]))
			break;

	return (str[i] ? 0 : 1);
}
