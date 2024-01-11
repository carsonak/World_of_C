#include "infix.h"
#define TESTING_SUB2

#ifdef TESTING_SUB2
/**
 * infiX_sub - subtracts numbers in an array
 * @n1_arr: number to be subtracted
 * @n2_arr: number to subtract
 *
 * Return: pointer to the result, NULL on failure
 */
uint32_t *infiX_sub(uint32_t *n1_arr, uint32_t *n2_arr)
{
	ssize_t a_sz = -1, b_sz = -1, res_sz = -1, g = 1, h = 1, k = 1, diff = 0;
	int64_t byt_res = 0;
	uint32_t *res = NULL;

	/*Get and adjust size of the arrays. Stored at index 0.*/
	if (n1_arr)
	{
		a_sz = n1_arr[0];
		while (!n1_arr[a_sz] && a_sz > 1)
			--a_sz;

		n1_arr[0] = a_sz;
	}

	if (n2_arr)
	{
		b_sz = n2_arr[0];
		while (!n2_arr[b_sz] && b_sz > 1)
			--b_sz;

		n2_arr[0] = b_sz;
	}

	/**
	 * Calculate and adjust size of the result
	 * res_sz = size of the larger number
	 * if both are the same size:
	 *		number of digits in result will be equal to the number of
	 *		digits left once the digits don't match anymore starting
	 *		from the most significant digit.
	 */
	res_sz = (a_sz > b_sz) ? a_sz : b_sz;
	if (a_sz > 0 && b_sz > 0 && a_sz == b_sz)
		for (; n1_arr[res_sz] && n2_arr[res_sz] && res_sz > 0; res_sz--)
			if (n1_arr[res_sz] != n2_arr[res_sz])
				break;

	/*Subtracting NULLs or matching numbers*/
	if (res_sz < 1)
	{
		res = calloc(3, sizeof(*res));
		if (!res)
			perror("Malloc fail");
		else
			res[0] = 1;

		return (res);
	}

	diff = res_sz;
	res = calloc((res_sz + 2), sizeof(*res));
	if (!res)
	{
		perror("Malloc fail");
		return (NULL);
	}

	res[0] = res_sz;
	while ((g <= a_sz || h <= b_sz) && k <= res_sz)
	{
		/*If n1 is greater than n2*/
		if (a_sz > b_sz || (a_sz == b_sz && n1_arr[diff] > n2_arr[diff]))
		{
			if (h <= b_sz)
				byt_res += (int64_t)n1_arr[g] - (int64_t)n2_arr[h];
			else
				byt_res += (int64_t)n1_arr[g];
		}
		else
		{
			if (g <= a_sz)
				byt_res += (int64_t)n2_arr[h] - (int64_t)n1_arr[g];
			else
				byt_res += (int64_t)n2_arr[h];
		}

		/*If subtraction results in a -ve number borrow from the next digits*/
		if (byt_res < 0 && k < (res_sz - 1))
		{
			byt_res += U32_ROLL;
			res[k] = byt_res % U32_ROLL;
			byt_res = -1;
		}
		else
		{ /*In a special case where subtraction of the */
			res[k] = byt_res % U32_ROLL;
			byt_res = 0;
		}

		++g;
		++h;
		++k;
	}

	/*Setting the -ve indicating bit if n2 is greater than n1*/
	if (a_sz < b_sz || (a_sz == b_sz && n1_arr[diff] < n2_arr[diff]))
		res[res_sz] |= U32_NEGBIT;

	return (res);
}
#else
/**
 * infiX_sub - subtracts numbers in a string
 * @n1: number to be subtracted
 * @n2: number to subtract
 *
 * Return: a string of the result, NULL on failure
 */
uint32_t *infiX_sub(uint32_t *n1_arr, uint32_t *n2_arr)
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

	if (a >= 0 && b >= 0 && a == b)
	{
		for (diff = 0; n1[diff] && n2[diff]; diff++)
		{
			if (n1[diff] == n2[diff])
				res_i--;
			else
				break;
		}
	}

	res = calloc(((++res_i) + 3), sizeof(*res));
	if (!res)
	{
		perror("Malloc fail");
		return (NULL);
	}

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
#endif
