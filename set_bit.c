#include <stdio.h>

unsigned int set_bit(unsigned int num, unsigned int bit);
int print_binary(unsigned int num, int spc);

/**/
unsigned int set_bit(unsigned int num, unsigned int index) {
  if (index < 32)
    return (num | (1 << index));
  else
    printf("Invalid index\n");

  return (num);
}

/**/
int print_binary(unsigned int num, int spc)
{
  if (num == 0)
    return (1);

  spc = print_binary(num >> 1, spc);

  spc += 1;
  printf("%d", num & 1);
  if (!(spc % 4) && (spc > 4))
    putchar(' ');

	return (spc);
}

/**/
int main(void) {
  unsigned int num = 12, num2 = 0, idx = 40;

  printf("Before = %u [", num);
  print_binary(num, 1);
  printf("]\n");
  num2 = set_bit(num, idx);
  printf("%u set at %u = %u [", num, idx, num2);
  print_binary(num2, 1);
  printf("]\n\n");

  idx = 6;
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

  idx = 6;
  num = 0;
  printf("Before = %u [", num);
  print_binary(num, 1);
  printf("]\n");
  num2 = set_bit(num, idx);
  printf("%u set at %u = %u [", num, idx, num2);
  print_binary(num2, 1);
  printf("]\n\n");

  idx = 9;
  num = 236;
  printf("Before = %u [", num);
  print_binary(num, 1);
  printf("]\n");
  num2 = set_bit(num, idx);
  printf("%u set at %u = %u [", num, idx, num2);
  print_binary(num2, 1);
  printf("]\n\n");

  return (0);
}
