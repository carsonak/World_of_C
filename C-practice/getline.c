#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * main - testing getline, read and EOF
 *
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	// char buffer[100];
	size_t len = 0;
	ssize_t nread;
	// int fd = STDIN_FILENO;
	FILE *fs = stdin;
	// char line[100] = {'H', 'e', 'l', 'l', 'o', '\n', '\0', 4};

	errno = 0;
	// fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
	// if (fd != -1)
	// 	write(fd, line, 8);
	// else
	// {
	// 	fwrite(strerror(errno), strlen(strerror(errno)), sizeof(char), stderr);
	// 	return (EXIT_FAILURE);
	// }
	fs = fopen("test", "w+");
	if (!fs)
	{
		fwrite(strerror(errno), strlen(strerror(errno)), sizeof(char), stderr);
		return (EXIT_FAILURE);
	}

	nread = getline(&line, &len, stdin);
	// nread = read(fd, buffer, 100);
	while (nread > 0)
	{
		// printf("[%ld]: ", nread);
		fwrite(line, nread, sizeof(char), fs);
		// fwrite(buffer, nread, sizeof(char), stdout);
		free(line);
		len = 0;
		nread = getline(&line, &len, stdin);
		// nread = read(fd, buffer, 100);
	}

	if (nread == -1 && errno)
	{
		fwrite(strerror(errno), strlen(strerror(errno)), sizeof(char), stderr);
		fclose(fs);
		// close(fd);
		exit(EXIT_FAILURE);
	}
	else if (nread < 1 && !errno)
	{
		if (feof(stdin) || !nread)
			printf("EOF [%ld]\n", nread);
		else
			printf("NO EOF\n");
	}

	fclose(fs);
	// close(fd);
	exit(EXIT_SUCCESS);
}

/**
 * How does getline or feof detect the EOF since it's an obsolete character?
 *
 * Info known:
 *
 * 1. 'ctrl + d' from the std input forces a program to accept current data in
 *  the std input.
 * 2. Hitting enter in the shell causes input to be read (this includes the
 * '\n') (unless within quotes)
 * 3. Pressing 'ctrl + d' on an empty line causes getline() to return -1
 * 4. This will also cause a shell to exit
 * 5. Normal files don't have an EOF character (since EOF isn't an actual char)
 *
 * Hypothesis:
 *
 * read() will process all input (within a specified number of bytes) into a
 * given buffer. However if 'ctrl + d' is pressed before the max number of bytes
 * is read, read() will immediately process whatever is currently in the input
 * into the buffer and return the number of bytes read upto that point. This
 * means that pressing 'ctrl + d' twice will first return the number of bytes
 * in the input currently and then return 0 as read() was forced to process 0
 * input. If there was no input pressing 'ctrl + d' will immediately return 0.
 *
 * getline() will continue reading bytes (even if ctrl+d is pressed) until a
 * new line is encountered, it will store the line in a buffer. The program
 * will then parse the whole line as a single input unlike with read. But, when
 * 'ctrl + d' is pressed twice, getline will process whatever is currently in
 * the input and return -1. If there was no input pressing 'ctrl + d' will
 * immediately return -1.
 *
 */
