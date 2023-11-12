#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

/**
 * main - testing getline
 *
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (nread >= 0)
	{
		nread = getline(&line, &len, stdin);
		printf("Retrieved line of length %ld:\n", nread);
		fwrite(line, nread, 1, stdout);
		free(line);
	}

	if (nread == -1)
		perror("getline() failure");

	exit(EXIT_SUCCESS);
}
