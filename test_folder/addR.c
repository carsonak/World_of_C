#include <stdio.h>
#include "main.h"

/**
 *sum - adds all numbers from 0 - a max value
 *@k: the max value
 *
 *Return: the sum.
 */

int sum(int k)
{
	if (k > 0)
	{
		printf("k is now: %d\n", k);
		return (k + sum(k - 1));
	}
	else if (k < 0)
	{
		printf("k is now: %d\n", k);
		return (k + sum(k + 1));
	}

	return (0);
}

/**
 *main - calls sum.
 *
 *Return: 0.
 */

int main(void)
{
	int result = sum(10);

	printf("%d", result);

	return (0);
}
