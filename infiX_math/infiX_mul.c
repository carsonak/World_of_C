#include "infix.h"
#define TESTING_MUL2

#ifdef TESTING_MUL2
/**
 * infiX_mul - multiplies numbers stored in strings.
 * @n1_arr: the first string with only decimals.
 * @n2_arr: the second string with only decimals.
 *
 * Return: string with the result, NULL on failure
 */
uint32_t *infiX_mul(uint32_t *n1_arr, uint32_t *n2_arr)
{
	uint64_t byt_mul = 0;
	ssize_t top = -1, botm = -1, c_mulsz = 0, t = 1, b = 1;
	uint32_t *c_mul = NULL, *prod = NULL, *total = NULL;

	/*Get and adjust size of the arrays. Stored at index 0.*/
	if (n1_arr)
	{
		top = n1_arr[0];
		while (!n1_arr[top] && top > 1)
			--top;

		n1_arr[0] = top;
	}

	if (n2_arr)
	{
		botm = n2_arr[0];
		while (!n2_arr[botm] && botm > 1)
			--botm;

		n2_arr[0] = botm;
	}

	/*Multiplication by zero or NULL*/
	if (!n1_arr || !n2_arr || (top == 1 && n1_arr[1] == 0) || (botm == 1 && n2_arr[1] == 0))
	{
		prod = calloc(3, sizeof(*prod));
		if (!prod)
			perror("Malloc fail");
		else
			prod[0] = 1;
	}
	else
	{
		for (b = 1; b <= botm; b++)
		{
			/*Skip multiplication by zero*/
			if (n2_arr[b] == 0)
				continue;

			/**
			 * Size of c_mul = Array size of top
			 * 					+ Current index of botm (b)
			 * Memalloc c_mul (+1 for storing size, +1 for end padding)
			 */
			c_mulsz = top + b;
			c_mul = calloc((c_mulsz + 2), sizeof(*c_mul));
			if (!c_mul)
			{
				perror("Malloc fail");
				return (NULL);
			}

			c_mul[0] = c_mulsz;
			byt_mul = 0;
			for (t = 1; t <= top; t++)
			{
				byt_mul += (uint64_t)n1_arr[t] * (uint64_t)n2_arr[b];
				/*Offset to current index of botm*/
				c_mul[(t - 1) + b] = byt_mul % U32_ROLL;
				byt_mul /= U32_ROLL;
			}

			c_mul[(t - 1) + b] = byt_mul % U32_ROLL;
			prod = infiX_add(total, c_mul);
			free(c_mul);
			if (total)
				free(total);

			if (!prod)
				return (NULL);

			total = prod;
		}
	}

	return (prod);
}
#else
/**
 * infiX_mul - multiplies numbers stored in strings.
 * @n1: the first string with only decimals.
 * @n2: the second string with only decimals.
 *
 * Return: string with the result, NULL on failure
 */
uint8_t *infiX_mul(uint8_t *n1, uint8_t *n2)
{
	ssize_t top = 0, botm = 0, c_dgt = 0, t = 0, b = 0;
	int byt_mul = 0;
	uint8_t *prod = NULL, *c_mul = NULL, *total = NULL;

	top = n1 ? (ssize_t)strlen((char *)n1) : 0;
	botm = n2 ? (ssize_t)strlen((char *)n2) : 0;
	if (top < 1 || botm < 1)
		return (NULL);

	for (b = botm - 1; b >= 0; b--)
	{
		if (n2[b] == '0')
			continue;

		c_dgt = top + (botm - b);
		c_mul = calloc((c_dgt + 2), sizeof(*c_mul));
		if (!c_mul)
		{
			perror("Malloc fail");
			return (NULL);
		}

		c_mul = memfill(c_mul, '0', (size_t)top, (size_t)(botm - b));
		c_mul[0] = '0';
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

	if (!prod)
	{
		prod = calloc(2, sizeof(*prod));
		if (!prod)
		{
			perror("Malloc fail");
			return (NULL);
		}

		prod[0] = '0';
	}

	return (prod);
}
#endif
