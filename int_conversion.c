#include "main.h"

/**
  * print_number - prints number.
  *
  *@num: integer passed.
  */
void print_number(int num, char *str)
{
	int var;
	char b;
	int index;

	var = 1;
	index = 0;
	if (num < 0)
	{
		str[index] = '-';
		num = -num;
		index++;
	}
	while (num / var >= 10)
	{
		var = var * 10;
	}
	while ( var > 0)
	{
		b = num / var;
		str[index] = (b + '0');
		num = num % var;
		var = var / 10;
		index++;
	}
	str[index] = '\0';
}
int main(void)
{
	char s[100];
	print_number(INT_MIN, s);
	printf("%s\n", s);
	return (0);
}
