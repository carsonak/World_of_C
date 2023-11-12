#include <stdio.h>
#include <stdlib.h>

/**
 * main - testing getenv
 *
 * Return: 0
 */
int main(void)
{
	char *environ;

	environ = getenv("PATH");
	printf("PATH : %s\n", environ);
	environ = getenv("HOME");
	printf("PATH : %s\n", environ);
	environ = getenv("ROOT");
	printf("PATH : %s\n", environ);

	return (0);
}
