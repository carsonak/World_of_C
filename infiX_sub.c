#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

uint8_t *infiX_sub(uint8_t *n1, uint8_t *n2);
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
		fprintf(stderr, "Insufficient digits to subtract");
		return (EXIT_FAILURE);
	}

	printf("%s - %s = %s\n", argv[1], argv[2], infiX_sub((uint8_t *)argv[1], (uint8_t *)argv[2]));
	return (EXIT_SUCCESS);
}

/**
 * infiX_sub - subtracts numbers in a string
 * @n1: number to be subtracted
 * @n2: number to subtract
 *
 * Return: a string of the result, NULL on failure
 */
uint8_t *infiX_sub(uint8_t *n1, uint8_t *n2)
{
	ssize_t a = 0, b = 0, res_i = 0, diff = 0;
	int byt_res = 0;
	uint8_t *res = NULL;

	n1 += n1 ? pad_char((char *)n1, "0") : 0;
	n2 += n2 ? pad_char((char *)n2, "0") : 0;
	a = n1 ? (ssize_t)(strlen((char *)n1) - 1) : -1;
	b = n2 ? (ssize_t)(strlen((char *)n2) - 1) : -1;
	res_i = (a > b) ? a : b;
	if (res_i < 0)
		return (NULL);

	if (a == b)
	{
		for (diff = 0; n1[diff] && n2[diff]; diff++)
		{
			if (n1[diff] == n2[diff])
				res_i--;
			else
				break;
		}
	}

	res = malloc(sizeof(*res) * ((++res_i) + 2));
	if (!res)
		return (NULL);

	res[res_i + 1] = '\0';
	if (a < b || (a == b && n1[diff] < n2[diff]))
		res[0] = '-';
	else
		res[0] = '0';

	while ((a >= 0 || b >= 0) && res_i > 0)
	{
		if (a > b || (a == b && n1[diff] > n2[diff]))
		{
			if (b >= 0)
				byt_res += ((n1[a] - '0') - (n2[b] - '0'));
			else
				byt_res += (n1[a] - '0');
		}
		else
		{
			if (a >= 0)
				byt_res += ((n2[b] - '0') - (n1[a] - '0'));
			else
				byt_res += (n2[b] - '0');
		}

		if (byt_res < 0 && res_i > 1)
		{
			byt_res += 10;
			res[res_i] = (byt_res % 10) + '0';
			byt_res = -1;
		}
		else
		{
			res[res_i] = abs(byt_res % 10) + '0';
			byt_res = 0;
		}

		--a;
		--b;
		--res_i;
	}

	return (res);
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
