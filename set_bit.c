#include <stdio.h>

unsigned int set_bit(unsigned int num, unsigned int bit);

unsigned int set_bit(unsigned int num, unsigned int index)
{
	if (index < 32)
		return (num | (1 << index));
	else
		printf("Invalid index\n");

	return (num);
}

int main(void)
{
	unsigned int num = 9, num2 = 0;
	
	printf("Before = %u\n", num);
	num2 = set_bit(num, 5);
	printf("After = %u\n", num2);

	return (0);
}
