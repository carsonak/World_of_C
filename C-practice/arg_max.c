#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * main - fills a file with 3,000,000 characters
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	unsigned int i = 0, max;
	int err = 0, fd = creat("max_bash.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	char *buff = "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV";

	max = (3000000 / strlen(buff));
	printf("max = %d (%d / %ld)\n", max, 3000000, strlen(buff));
	if (fd == -1)
	{
		perror("Failed to open max_bash.txt");
		return (EXIT_FAILURE);
	}

	for (i = 0; i < max; i++)
	{
		err = write(fd, buff, (sizeof(*buff) * strlen(buff)));
		if (err == -1)
		{
			perror("Failed to write");
			close(fd);
			return (EXIT_FAILURE);
		}
	}

	close(fd);
	return (EXIT_SUCCESS);
}
