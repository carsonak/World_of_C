#include "infix.h"

/**
 * str_u32 - convert a string of numbers to a 32 bit int array
 * @num: a string of only integers
 *
 * Description: This function converts a string of numbers to an array of
 * unsigned 32 bit integers.
 * The array shall be in little endian style whereby the lower value numbers
 * will be placed in the lower indices. Index 0 will have a value indicating
 * the size of the array.
 *
 * Return: an array of 32 bit ints, NULL on failure
 */
uint32_t *str_u32(uint8_t *num)
{
	size_t u32arr_sz = 0, len = 0, g = 0, h = 0;
	uint32_t *u32arr = NULL;
	int i = 0, mul = 1;

	if (!num)
		return (NULL);

	len = strlen((char *)num);
	u32arr_sz = (len / 6) + ((len % 6) ? 1 : 0);
	u32arr = calloc(sizeof(*u32arr), u32arr_sz + 2);
	if (!u32arr)
		return (NULL);

	/*Index 0 will have the size of the array*/
	u32arr[0] = u32arr_sz;
	for (h = u32arr_sz, g = 0; h > 0 && g < len; h--)
	{
		mul = ((len - (g + 1)) > 5) ? 5 : (len - (g + 1));

		for (i = 0; i < 6 && (g + i) < len; i++, mul--)
			u32arr[h] += (num[g + i] - '0') * (uint32_t)(pow(10, mul));

		g += 6;
	}

	return (u32arr);
}

/**
 * u32_str - convert a 32 bit int array to a string
 * @u32a: a 32 bit array
 *
 * Description: This function converts an array of unsigned 32 bit integers
 * to a string.
 * The array shall be in little endian style whereby the lower value numbers
 * will be placed in the lower indices. Index 0 will have a value indicating
 * the size of the array.
 *
 * Return: a string of numbers, NULL on failure
 */
uint8_t *u32_str(uint32_t *u32a)
{
	size_t u32arr_sz = 0, len = 0, g = 0, h = 0, i = 0;
	uint8_t *num = NULL;
	ssize_t temp = 0, div = 1;

	if (!u32a)
		return (NULL);

	u32arr_sz = u32a[0];
	len = u32arr_sz * 6;
	num = calloc(sizeof(*num), (len + 1));
	if (!num)
		return (NULL);

	for (h = u32arr_sz, g = 0; h > 0 && g < len; h--)
	{
		temp = u32a[h];
		while (temp / div >= 10)
			div = div * 10;

		for (i = 0; i < 6; i++)
		{
			if (temp)
				num[g + i] = (temp / div) + '0';
			else if (h > 1 && !temp)
				num[g + i] = '0';
			else if (h <= 1 && !temp)
			{
				num[g + i] = '0';
				break;
			}

			if (div)
			{
				temp %= div;
				div /= 10;
			}
		}

		g += 6;
		div = 1;
	}

	if (i)
		num[(g - 6) + i] = '\0';

	return (num);
}

#ifdef TESTING_CONVERTERS
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

/**
 * main - testing entry point
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	size_t i = 0, g = 0;
	uint32_t *ntemp = NULL, len = 0;
	uint8_t *stemp = NULL;
	char *nstr[] = {
		"123456",
		"1000000",
		"909897000000234587",
		"0",
		"000000123",
		"12",
		"000001000002000003000004000000",
		NULL,
	};

	while (nstr[g])
	{
		printf("%s\n", &nstr[g][pad_char(nstr[g], "0")]);
		ntemp = str_u32((uint8_t *)(&nstr[g][pad_char(nstr[g], "0")]));
		if (!ntemp)
			return (EXIT_FAILURE);

		len = ntemp[0];
		for (i = len; i > 0; i--)
		{
			if (i > 1)
				printf("%06d", (int)ntemp[i]);
			else
				printf("%d", (int)ntemp[i]);
		}

		printf(" [%d: Blocks]\n", (int)len);
		stemp = u32_str(ntemp);
		free(ntemp);
		if (stemp)
			printf("%s\n\n", (char *)stemp);
		else
			return (EXIT_FAILURE);

		free(stemp);
		ntemp = NULL;
		stemp = NULL;
		g++;
	}

	return (EXIT_SUCCESS);
}
#endif
