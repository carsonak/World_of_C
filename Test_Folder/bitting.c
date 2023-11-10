#define _OPEN_SYS_ITOA_EXT
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char num = 2, buf[33];
	int cnt = 0;

	printf("Sizeof char %ld bits\n", sizeof(char) * 8);
	printf("Sizeof int %ld bits\n", sizeof(int) * 8);
	printf("%d: %d\n", cnt, num);
	while (num)
	{
		num <<= 1;
		cnt++;
		printf("%d: %d[%s]\n", cnt, num, itoa(num, buf, 2));
	}
	return (0);
}
