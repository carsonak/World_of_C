#include <limits.h>
#include <stdio.h>

/**
 * int_to_str - stores a number in a string
 * @num: integer passed.
 * @str: buffer to store the number
 */
static void int_to_str(int num, char *str)
{
	int var = 1, index = 0;
	char b;

	if (num < 0)
	{
		str[index] = '-';
		num = -num;
		index++;
	}

	while (num / var >= 10)
		var = var * 10;

	while (var > 0)
	{
		b = (num / var) + '0';
		str[index] = b;
		num = num % var;
		var = var / 10;
		index++;
	}

	str[index] = '\0';
}

/**
 * main - entry point
 *
 * Return: 0
 */
int main(void)
{
	char s[100];

	int_to_str(INT_MIN, s);
	printf("%s\n", s);
	return (0);
}
