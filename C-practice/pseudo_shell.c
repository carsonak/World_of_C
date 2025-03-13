#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * main - practice with strtok, i/o, forking
 *
 * Return: always 0
 */
int main(void)
{
	char *argv[3], input[] = "/usr/bin/ls -l";
	char **newenviron = __environ;
	pid_t frk1, fork_err;
	int err = 0, status, i, fd = 0;

	argv[0] = strtok(input, " ");
	printf("%s\n", argv[0]);
	argv[1] = strtok(NULL, " ");
	printf("%s\n", argv[1]);
	argv[2] = strtok(NULL, " ");

	frk1 = fork();

	if (frk1 == -1)
		perror("Couldn't fork");
	else if (frk1 == 0)
	{
		fd = creat("child_env.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
			perror("\nFailed to open file");
		else
		{
			for (i = 0; newenviron[i]; i++)
			{
				err = write(fd, newenviron[i], (sizeof(**newenviron) * strlen(newenviron[i])));
				if (err == -1)
				{
					perror("\nFailed to write to file");
					break;
				}
				else
					write(fd, "\n", sizeof(**newenviron));
			}

			err = close(fd);
			if (err == -1)
				perror("\nFailed to close file");
			else
				printf("File \"child_env.txt\" has been created and child environment variables saved.\n");
		}

		err = execve(argv[0], argv, newenviron);
		if (err == -1)
		{
			close(fd);
			perror("\nCouldn't execute");
		}
	}
	else
	{
		fork_err = wait(&status);
		if (fork_err == -1)
			perror("\nWait error");

		fd = creat("parent_env.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
			perror("\nFailed to open file");
		else
		{
			for (i = 0; newenviron[i]; i++)
			{
				err = write(fd, newenviron[i], (sizeof(**newenviron) * strlen(newenviron[i])));
				if (err == -1)
				{
					perror("\nFailed to write to file");
					break;
				}
				else
					write(fd, "\n", sizeof(**newenviron));
			}
			err = close(fd);
			if (err == -1)
				perror("\nFailed to close file");
			else
				printf("File \"parent_env.txt\" has been created and parent environment variables saved.\n");
		}
	}

	return (0);
}
