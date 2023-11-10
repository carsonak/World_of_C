#include <stdio.h>

/**
 *main - Prints an equilateral right angled triangle of user's size.
 *
 *Return: the numbers in the string or 0 if none.
 */

int main(void)
{
	int h, i, j;

	while (1)
	{
		printf("What is the height of your triangle?");
		scanf("%d", &h);
		if (h <= 0)
		{
			break;
		}
		for (i = 1; i <= h; i++)
		{
			j = 1;
			while (j <= i)
			{
				printf("#");
				j++;
			}
			printf("\n");
		}
	}
	return (0);
}
