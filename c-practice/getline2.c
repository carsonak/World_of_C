#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * main - more getline practice
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t sz = 0;
	ssize_t rd_sz = 1;

	rd_sz = getline(&line, &sz, stdin);
	while (rd_sz > 0)
	{
		printf("[%ld] %s\n", rd_sz, line);
		rd_sz = getline(&line, &sz, stdin);
	}

	if (feof(stdin))
		printf("EOF [%ld]\n", sz);
	else
		perror("Fail");

	return (EXIT_SUCCESS);
}
