#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

uint8_t *infiX_div(uint8_t *dividend, uint8_t *divisor, uint8_t **remainder);
uint8_t *infiX_sub(uint8_t *n1, uint8_t *n2);
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
int main(int argc, uint8_t *argv[])
{
	uint8_t *rem = calloc(100, sizeof(*rem));

	if (argc != 3)
	{
		fprintf(stderr, "USAGE: %s <dividend> <divisor>", argv[0]);
		return (EXIT_FAILURE);
	}
	else if (!isdigit(argv[1][0]) || !isdigit(argv[2][0]))
	{
		fprintf(stderr, "Insufficient digits to divide");
		return (EXIT_FAILURE);
	}

	infiX_div((uint8_t *)argv[1], (uint8_t *)argv[2], &rem);
	return (EXIT_SUCCESS);
}

/**
 * infiX_div - divides
 * @dividend: d
 * @divisor: d
 * @remainder: r
 *
 * Return: string with the results, NULL on failure
 */
uint8_t *infiX_div(uint8_t *dividend, uint8_t *divisor, uint8_t **remainder)
{
	unsigned int len_end = strlen(dividend), len_sor = strlen(divisor), i = 0;
	int len_q = 0, ds = 0, de = 0;
	uint8_t *quotient = NULL;

	if (len_end < len_sor)
	{
		strcpy((uint8_t *)(*remainder), dividend);
		return (NULL);
	}
	else if (len_end == len_sor)
		return (NULL);

	len_q = (len_end - len_sor) + 2;
	quotient = calloc(len_q, sizeof(*quotient));
	if (!quotient)
	{
		perror("Malloc fail");
		return (NULL);
	}

	for (i = len_sor; i < len_end; i++)
	{
		/* code */
	}

	return (quotient);
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
	ssize_t a = 0, t = 0, res_i = 0, diff = 0;
	int byt_res = 0;
	uint8_t *res = NULL;

	n1 += n1 ? pad_char((char *)n1, "0") : 0;
	n2 += n2 ? pad_char((char *)n2, "0") : 0;
	a = n1 ? (ssize_t)(strlen((char *)n1) - 1) : -1;
	t = n2 ? (ssize_t)(strlen((char *)n2) - 1) : -1;
	res_i = (a > t) ? a : t;
	if (res_i < 0)
		return (NULL);

	if (a == t)
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
	if (a < t || (a == t && n1[diff] < n2[diff]))
		res[0] = '-';
	else
		res[0] = '0';

	while ((a >= 0 || t >= 0) && res_i > 0)
	{
		if (a > t || (a == t && n1[diff] > n2[diff]))
		{
			if (t >= 0)
				byt_res += ((n1[a] - '0') - (n2[t] - '0'));
			else
				byt_res += (n1[a] - '0');
		}
		else
		{
			if (a >= 0)
				byt_res += ((n2[t] - '0') - (n1[a] - '0'));
			else
				byt_res += (n2[t] - '0');
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
		--t;
		--res_i;
	}

	return (res);
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
	ssize_t top = 0, botm = 0, c_dgt = 0, b = 0, t = 0;
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
		for (t = top - 1; t >= 0; t--)
		{
			byt_mul += ((n1[t] - '0') * (n2[b] - '0'));
			c_mul[t + 1] = (byt_mul % 10) + '0';
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
	ssize_t a = 0, t = 0, byt_sum = 0, sum_i = 0;
	uint8_t *sum = NULL;

	n1 += n1 ? pad_char((char *)n1, "0") : 0;
	n2 += n2 ? pad_char((char *)n2, "0") : 0;
	a = n1 ? (ssize_t)(strlen((char *)n1) - 1) : -1;
	t = n2 ? (ssize_t)(strlen((char *)n2) - 1) : -1;
	sum_i = (a > t) ? a : t;
	if (sum_i < 0)
		return (NULL);

	sum = malloc(sizeof(*sum) * ((++sum_i) + 2));
	if (!sum)
		return (NULL);

	sum[sum_i + 1] = '\0';
	sum[0] = '0';
	while (a >= 0 || t >= 0 || byt_sum > 0)
	{
		if (a >= 0)
		{
			byt_sum += (n1[a] - '0');
			--a;
		}

		if (t >= 0)
		{
			byt_sum += (n2[t] - '0');
			--t;
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
