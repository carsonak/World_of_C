#include <stdlib.h>
#include <stdio.h>

/**
 * main - entry point
 *
 * Return: 0
 */
int main(void)
{
	size_t i;

	/*printf("(void *)i ==> %p\n", (void *)i);*/
	for (; i < 100000000000000;)
		*(size_t *)(i++) = 'A';

	return (0);
}
