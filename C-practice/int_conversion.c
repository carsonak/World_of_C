#include "main.h"

/**
 * print_number - stores a number in a string
 * @num: integer passed.
 * @str: buffer to store the number
 */
void print_number(int num, char *str)
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

	print_number(INT_MIN, s);
	printf("%s\n", s);
	return (0);
}
