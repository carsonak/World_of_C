#include <stdio.h>
#include <unistd.h>
#include <limits.h>

/**
 * main - converts decimals to octal and stores in a buffer
 *
 * Return: always 0
 */
int main(void)
{
	long int num, var = 8, buf_i = 0;
	int count = 0, backup = 0;
	char buff[10]; /*Buffer*/

	num = 897389475; /*Test case*/
	if (num < 0) /*How to convert to unsigned int????*/
		num = -num;

	/**
	 * Getting the number of digits to be printed by counting
	 * the powers of 8 until they exceed the given number
	 */
	while (var < num)
	{
		var = var * 8;
		count++;
	}

	backup = count;
	/**
	 * Storing the digits in a buffer from the right-most digit
	 * to the left-most digit.
	 */
	while (count >= 0)
	{
		/*Should account for buffer overflow here*/
		buff[buf_i + count] = num % 8 + '0';
		num = num / 8;
		count--;
	}

	buf_i = buf_i + backup; /*Updating index of the buffer*/
	write(1, buff, buf_i + 1);
	putchar('\n');

	return (0);
}
