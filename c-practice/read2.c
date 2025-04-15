#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * main - more read practice
 *
 * Return: 0 on success
 */
int main(void)
{
	char buff[100] = {'\0'};
	size_t i = 0;
	ssize_t rd_sz = 0;

	rd_sz = read(STDIN_FILENO, buff, 100);
	while (rd_sz > 0)
	{
		printf("[%ld] %s\n", rd_sz, buff);
		i++;
		rd_sz = read(STDIN_FILENO, buff, 100);
	}

	if (!rd_sz)
		printf("EOF [%ld loops]\n", i);
	else
		perror("Fail");

	return (EXIT_SUCCESS);
}
