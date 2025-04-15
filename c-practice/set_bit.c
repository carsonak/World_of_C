#include <stdio.h>

unsigned int set_bit(unsigned int num, unsigned int bit);
void print_binary(unsigned int num);
void print_bi(unsigned int num, int *spc);

/**
 * set_bit - sets the value of a bit in an int at the given index
 * @num: the usigned int to be modified
 * @index: the index of the bit to be set
 *
 * Return: the new value of num
 */
unsigned int set_bit(unsigned int num, unsigned int index)
{
	if (index >= 32)
		printf("Invalid index\n");
	else
		return (num | (1 << index));

	return (num);
}

/**
 * print_bi - prints an int in binary and adds spacing for readability
 * @num: unsigned int to be converted
 * @spc: address of the tracker for the spacing
 */
void print_bi(unsigned int num, int *spc)
{
	if (num == 0)
		return;

	print_bi(num >> 1, spc);

	printf("%d", num & 1);
	if (*spc % 4 == 0)
		putchar(' ');

	(*spc)++;
}

/**
 * print_binary - calls the helper function print_bi to print in binary
 * @num: unsigned int to be printed
 */
void print_binary(unsigned int num)
{
	int spacer = 1;

	if (num > 0)
		print_bi(num, &spacer);
	else
		putchar('0');
}

/**
 * main - entry point
 *
 * Return: ALways 0
 */
int main(void)
{
	unsigned int num = 12, num2 = 0, idx = 40;

	printf("Before = %u [", num);
	print_binary(num);
	printf("]\n");
	num2 = set_bit(num, idx);
	printf("%u set at %u = %u [", num, idx, num2);
	print_binary(num2);
	printf("]\n\n");

	idx = 6;
	printf("Before = %u [", num);
	print_binary(num);
	printf("]\n");
	num2 = set_bit(num, idx);
	printf("%u set at %u = %u [", num, idx, num2);
	print_binary(num2);
	printf("]\n\n");

	idx = -1;
	printf("Before = %u [", num);
	print_binary(num);
	printf("]\n");
	num2 = set_bit(num, idx);
	printf("%u set at %u = %u [", num, idx, num2);
	print_binary(num2);
	printf("]\n\n");

	idx = 6;
	num = 0;
	printf("Before = %u [", num);
	print_binary(num);
	printf("]\n");
	num2 = set_bit(num, idx);
	printf("%u set at %u = %u [", num, idx, num2);
	print_binary(num2);
	printf("]\n\n");

	idx = 9;
	num = 236;
	printf("Before = %u [", num);
	print_binary(num);
	printf("]\n");
	num2 = set_bit(num, idx);
	printf("%u set at %u = %u [", num, idx, num2);
	print_binary(num2);
	printf("]\n\n");

	return (0);
}
