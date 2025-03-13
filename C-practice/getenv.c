#include <stdio.h>
#include <stdlib.h>

/**
 * main - testing getenv
 *
 * Return: 0
 */
int main(void)
{
	char *env_var;

	env_var = getenv("PATH");
	printf("PATH : %s\n", env_var);
	env_var = getenv("HOME");
	printf("PATH : %s\n", env_var);
	env_var = getenv("ROOT");
	printf("PATH : %s\n", env_var);

	return (0);
}
