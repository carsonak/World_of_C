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

void print_binary(unsigned int num)
{
	while (num)
	{
		printf("%d", num & 1);
		num >>= 1;
	}
}

int main(void)
{
	unsigned int num = 3421, num2 = 0, idx = 40;
	
	printf("Before = %u [", num);
	print_binary(num);
	printf("]\n");
	num2 = set_bit(num, idx);
	printf("After = %u [", num2);
	print_binary(num2);
	printf("]\n");

	return (0);
}
