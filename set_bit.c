#include <stdio.h>

unsigned int set_bit(unsigned int num, unsigned int bit);
void print_binary(unsigned int num, unsigned int spc);

unsigned int set_bit(unsigned int num, unsigned int index)
{
	if (index < 32)
		return (num | (1 << index));
	else
		printf("Invalid index\n");

	return (num);
}

void print_binary(unsigned int num, unsigned int spc)
{
	if (num == 0)
		return;

	spc++;
	print_binary(num >> 1, spc++);
	
	printf("%d", num & 1);
	if (!(spc % 4) && spc > 4)
		putchar(' ');
	
}

int main(void)
{
	unsigned int num = 341, num2 = 0, idx = 40;
	
	printf("Before = %u [", num);
	print_binary(num, 1);
	printf("]\n");
	num2 = set_bit(num, idx);
	printf("%u set at %u = %u [", num, idx, num2);
	print_binary(num2, 1);
	printf("]\n\n");

	idx = 13;
	printf("Before = %u [", num);
	print_binary(num, 1);
	printf("]\n");
	num2 = set_bit(num, idx);
	printf("%u set at %u = %u [", num, idx, num2);
	print_binary(num2, 1);
	printf("]\n\n");

	idx = -1;
	printf("Before = %u [", num);
	print_binary(num, 1);
	printf("]\n");
	num2 = set_bit(num, idx);
	printf("%u set at %u = %u [", num, idx, num2);
	print_binary(num2, 1);
	printf("]\n\n");

	return (0);
}
