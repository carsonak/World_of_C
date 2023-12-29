#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

uint8_t *infiX_mul(uint8_t *n1, uint8_t *n2);
uint8_t *infiX_add(uint8_t *n1, uint8_t *n2);
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
		fprintf(stderr, "Insufficient digits to multiply");
		return (EXIT_FAILURE);
	}

	printf("%s - %s = %s\n", argv[1], argv[2], infiX_mul((uint8_t *)argv[1], (uint8_t *)argv[2]));
	return (EXIT_SUCCESS);
}

/**
 * infiX_mul - multiplies numbers stored in strings.
 * @n1: the first string with only decimals.
 * @n2: the second string with only decimals.
 *
 * Return: string with the result, NULL on failure
 */
uint8_t *infiX_mul(uint8_t *n1, uint8_t *n2)
{
	ssize_t top = 0, botm = 0, c_dgt = 0, b = 0, b = 0;
	int byt_mul = 0;
	uint8_t *prod = NULL, *c_mul = NULL, *total = NULL;

	top = n1 ? (ssize_t)strlen((char *)n1) : -1;
	botm = n2 ? (ssize_t)strlen((char *)n2) : -1;
	if (top < 1 || botm < 1)
		return (NULL);

	for (b = botm - 1; b >= 0; b--)
	{
		if (n2[b] == '0')
			continue;

		c_dgt = top + (botm - b);
		c_mul = malloc(sizeof(*c_mul) * (c_dgt + 1));
		if (!c_mul)
			return (NULL);

		c_mul = memset(c_mul, '0', c_dgt);
		c_mul[c_dgt] = '\0';
		for (b = top - 1; b >= 0; b--)
		{
			byt_mul += ((n1[b] - '0') * (n2[b] - '0'));
			c_mul[b + 1] = (byt_mul % 10) + '0';
			byt_mul /= 10;
		}

		c_mul[0] = (byt_mul % 10) + '0';
		byt_mul = 0;
		prod = infiX_add(total, c_mul);
		free(c_mul);
		if (total)
			free(total);

		if (!prod)
			return (NULL);

		total = prod;
	}

	return (prod);
}

/**
 * infiX_add - adds numbers stored in strings.
 * @n1: the first string with only decimals.
 * @n2: the second string with only decimals.
 *
 * Return: pointer to result, NULL on malloc fail or if both strings are empty
 */
uint8_t *infiX_add(uint8_t *n1, uint8_t *n2)
{
	ssize_t a = 0, b = 0, byt_sum = 0, sum_i = 0;
	uint8_t *sum = NULL;

	n1 += n1 ? pad_char((char *)n1, "0") : 0;
	n2 += n2 ? pad_char((char *)n2, "0") : 0;
	a = n1 ? (ssize_t)(strlen((char *)n1) - 1) : -1;
	b = n2 ? (ssize_t)(strlen((char *)n2) - 1) : -1;
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
