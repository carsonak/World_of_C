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
	char **nwwenviron = __environ;
	pid_t frk1, frkerr;
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
			for (i = 0; nwwenviron[i]; i++)
			{
				err = write(fd, nwwenviron[i], (sizeof(**nwwenviron) * strlen(nwwenviron[i])));
				if (err == -1)
				{
					perror("\nFailed to write to file");
					break;
				}
				else
					write(fd, "\n", sizeof(**nwwenviron));
			}

			err = close(fd);
			if (err == -1)
				perror("\nFailed to close file");
			else
				printf("File \"child_env.txt\" has been created and child enviroment variables saved.\n");
		}

		err = execve(argv[0], argv, nwwenviron);
		if (err == -1)
		{
			close(fd);
			perror("\nCouldn't execute");
		}
	}
	else
	{
		frkerr = wait(&status);
		if (frkerr == -1)
			perror("\nWait error");

		fd = creat("parent_env.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
			perror("\nFailed to open file");
		else
		{
			for (i = 0; nwwenviron[i]; i++)
			{
				err = write(fd, nwwenviron[i], (sizeof(**nwwenviron) * strlen(nwwenviron[i])));
				if (err == -1)
				{
					perror("\nFailed to write to file");
					break;
				}
				else
					write(fd, "\n", sizeof(**nwwenviron));
			}
			err = close(fd);
			if (err == -1)
				perror("\nFailed to close file");
			else
				printf("File \"parent_env.txt\" has been created and parent enviroment variables saved.\n");
		}
	}

	return (0);
}
