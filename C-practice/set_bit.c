#include <stdio.h>

unsigned int set_bit(unsigned int num, unsigned int bit);
void print_bits(unsigned int num);

unsigned int set_bit(unsigned int num, unsigned int index)
{
	if (index < 32)
		return (num | (1 << index));
	else
		printf("Invalid index\n");

	return (num);
}

void print_bits(unsigned int num)
{
	while (num)
		{
			printf("%d", num & 1);
			num >>= 1;
		}
}

int main(void)
{
	unsigned int num = 9, num2 = 0;
	
	printf("Before = %u [", num);
	print_bits(num);
	printf("]\n");
	num2 = set_bit(num, 5);
	printf("After = %u [", num2);
	print_bits(num2);
	printf("]\n");

	return (0);
}
