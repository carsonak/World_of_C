#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

uint8_t *sieve_o_atkins(uint64_t range);
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

	int64_t limit = 0, ulimit = 0;
	int64_t i, j, count, x, y, z;
	uint8_t *sieb = NULL;

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
	sieb = sieve_o_atkins(limit);
	if (!sieb)
		return (EXIT_FAILURE);

	/*printf("Primes in range %ld:\n", limit);*/
	for (i = 0, count = 0; i <= limit; i++)
	{
		if (sieb[i / 8] & (1 << (i % 8)))
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
 * sieve_o_atkins - generates a sieve to find prime numbers upto a limit
 * @range: the range from 0
 *
 * Description: Uses a bit mask to mark prime numbers o the number line
 *
 * Return: a pointer to the sieve, NULL on failure
 */
uint8_t *sieve_o_atkins(uint64_t range)
{
	int64_t limit = range, ulimit = 0;
	int64_t i, j, x, y, z;
	uint8_t *sieb = NULL;

	sieb = calloc(((range / 8) + 1), sizeof(*sieb));
	if (!sieb)
	{
		perror("Sieve alocation failed\n");
		return (NULL);
	}

	ulimit = sqrt(limit);
	for (x = 1; x <= ulimit; x++)
	{
		for (y = 1; y <= ulimit; y++)
		{
			z = (4 * x * x) + (y * y);
			if (z <= limit &&
				(z % 60 == 1 || z % 60 == 13 || z % 60 == 17 || z % 60 == 29 ||
				 z % 60 == 37 || z % 60 == 41 || z % 60 == 49 || z % 60 == 53))
			{
				if (sieb[z / 8] & (1 << (z % 8)))
					sieb[z / 8] &= ~(1 << (z % 8));
				else
					sieb[z / 8] |= (1 << (z % 8));
			}

			z = (3 * x * x) + (y * y);
			if (z <= limit &&
				(z % 60 == 7 || z % 60 == 19 || z % 60 == 31 || z % 60 == 43))
			{
				if (sieb[z / 8] & (1 << (z % 8)))
					sieb[z / 8] &= ~(1 << (z % 8));
				else
					sieb[z / 8] |= (1 << (z % 8));
			}

			z = (3 * x * x) - (y * y);
			if (x > y && z <= limit &&
				(z % 60 == 11 || z % 60 == 23 || z % 60 == 47 || z % 60 == 59))
			{
				if (sieb[z / 8] & (1 << (z % 8)))
					sieb[z / 8] &= ~(1 << (z % 8));
				else
					sieb[z / 8] |= (1 << (z % 8));
			}
		}
	}

	sieb[2 / 8] |= (1 << (2 % 8));
	sieb[3 / 8] |= (1 << (3 % 8));
	sieb[5 / 8] |= (1 << (5 % 8));
	for (i = 5; i <= ulimit; i++)
		if (sieb[i / 8] & (1 << (i % 8)))
			for (j = 1; (j * i * i) <= limit; j++)
				sieb[(j * i * i) / 8] &= ~(1 << ((j * i * i) % 8));

	return (sieb);
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
