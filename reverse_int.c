#include <stdio.h>
#include <string.h>

int reverse(int x);
int str_to_int(char *num_str, int size);
char check_32(char *num_str, int size);
void int_to_str(char *num_str, int size, int x);

/**
 * reverse - reverse the order of digits in a number
 * @x: the number to reverse
 *
 * Return: the reversed number
 */
int reverse(int x)
{
	char num_str[12] = {0};

	int_to_str(num_str, 12, x);

	return (str_to_int(num_str, strlen(num_str)));
}

/**
 * str_to_int - converts a string of numbers to a 32 bit int
 * @num_str: the string with the number
 * @size: size of the string
 *
 * Return: the number
 */
int str_to_int(char *num_str, int size)
{
	int num = 0, i = 0;

	if (!check_32(num_str, size))
		return (0);

	for (i = 0; i < size && i < 10; i++)
	{
		if (num_str[i])
		{
			num *= 10;
			num += num_str[i] - '0';
		}
	}

	if (num_str[10])
		num *= -1;

	return (num);
}

/**
 * check_32 - checks if a number in a string is a 32 bit number
 * @num_str: the string
 * @size: size of the string
 *
 * Return: 1 if it is a 32 bit int, else 0
 */
char check_32(char *num_str, int size)
{
	char upper[] = {'2', '1', '4', '7', '4', '8', '3', '6', '4', '7'};
	int len = 10, i = 0;

	if (!num_str)
		return (0);

	if (size < len)
		return (1);

	if (num_str[10])
		upper[len - 1] += 1;

	for (i = 0; i < len && i < size; i++)
	{
		if (num_str[i] > upper[i])
			return (0);
		else if (num_str[i] < upper[i])
			break;
	}

	return (1);
}

/**
 * int_to_str - converts ints to strings
 * @num_str: a buffer to store the string
 * @size: size of the string
 * @x: the int to convert
 */
void int_to_str(char *num_str, int size, int x)
{
	int i = 0, neg = 0;

	if (x < 0)
	{
		num_str[size - 2] = '-';
		neg = 1;
	}

	for (i = 0; x && i < size - 2; i++)
	{
		num_str[i] = (x % 10);
		if (neg && num_str[i])
			num_str[i] *= -1;

		num_str[i] += '0';
		x /= 10;
	}
}

/**
 * main - Entry point
 *
 * Return: 0
 */
int main(void)
{
	int x = 123;

	printf("%d -> %d\n", x, reverse(x));
	x = -67890;
	printf("%d -> %d\n", x, reverse(x));
	x = 600000;
	printf("%d -> %d\n", x, reverse(x));
	x = 2147483647;
	printf("%d -> %d\n", x, reverse(x));
	x = -2147483648;
	printf("%d -> %d\n", x, reverse(x));
	x = -2147483641;
	printf("%d -> %d\n", x, reverse(x));

	return (0);
}
