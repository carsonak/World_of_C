#include "infix.h"

/**
 * strtonl - converts n elements of a string to long int
 * @num: pointer to a string with decimals
 * @nelem: max elements to convert
 *
 * Return: a long
 */
long strtonl(char *num, size_t nelem)
{
	size_t i = 0;
	long nam = 0;

	for (i = 0; i < nelem; i++)
	{
		if (isdigit(num[i]))
			nam = (nam * 10) + (num[i] - '0');
		else
			break;
	}

	return (nam);
}
