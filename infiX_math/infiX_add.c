#include "infix.h"
#define TESTING_ADD2

#ifdef TESTING_ADD2
/**
 * infiX_add - adds numbers stored in strings.
 * @n1: the first string with only decimals.
 * @n2: the second string with only decimals.
 *
 * Return: pointer to result, NULL on failure
 */
uint8_t *infiX_add(uint8_t *n1, uint8_t *n2)
{
	ssize_t a_sz = -1, b_sz = -1, sum_sz = 0, g = 1, h = 1, k = 1;
	int64_t byt_sum = 0;
	uint32_t *sum = NULL, *n1_arr = NULL, *n2_arr = NULL;
	uint8_t *total = NULL;

	/**
	 * Send n1 and n2 to the converters (offset pointer by number of leading zeros)
	 * Get size of the resulting arrays (stored at index 0), set to -ve if NULL
	 */
	if (n1 && *n1)
	{
		n1_arr = str_u32(&n1[pad_char((char *)n1, "0")]);
		if (!n1_arr)
			return (NULL);
		else
			a_sz = n1_arr[0];
	}

	if (n2 && *n2)
	{
		n2_arr = str_u32(&n2[pad_char((char *)n2, "0")]);
		if (!n2_arr)
		{
			if (n1_arr)
				free(n1_arr);

			return (NULL);
		}
		else
			b_sz = n2_arr[0];
	}

	/**
	 * Calculate size of the sum array (larger of a_sz or b_sz, +1 for a carry)
	 * Memalloc sum_array (+1 for size block, +1 for end padding)
	 */
	sum_sz = ((a_sz > b_sz) ? a_sz : b_sz) + 1;
	if (sum_sz < 1)
		return (NULL);

	sum = calloc((sum_sz + 2), sizeof(*sum));
	if (!sum)
	{
		perror("Malloc fail");
		if (n1_arr)
			free(n1_arr);

		if (n2_arr)
			free(n2_arr);

		return (NULL);
	}

	sum[0] = sum_sz;
	while (g <= a_sz || h <= b_sz || byt_sum > 0)
	{
		if (g <= a_sz)
		{
			byt_sum += n1_arr[g];
			++g;
		}

		if (h <= b_sz)
		{
			byt_sum += n2_arr[h];
			++h;
		}

		sum[k] = byt_sum % (U32_ROLL);
		byt_sum /= (U32_ROLL);
		++k;
	}

	total = u32_str(sum);
	free(sum);
	if (n1_arr)
		free(n1_arr);

	if (n2_arr)
		free(n2_arr);

	if (!total)
		return (NULL);

	return (total);
}
#else
/**
 * infiX_add - adds numbers stored in strings.
 * @n1: the first string with only decimals.
 * @n2: the second string with only decimals.
 *
 * Return: pointer to result, NULL on failure
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

	sum = calloc(((++sum_i) + 2), sizeof(*sum));
	if (!sum)
	{
		perror("Malloc fail");
		return (NULL);
	}

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
#endif
