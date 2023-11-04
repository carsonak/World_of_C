#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - practice with strtok
 *
 * Return: always 0
 */
int main(void)
{
	char *argv[3], **nwwenviron = __environ, input[] = "./ls.sh";
	pid_t frk1, frkerr;
	int err = 0, status;

	argv[0] = strtok(input, " ");
	argv[1] = strtok(input, " ");
	argv[2] = NULL;
	frk1 = fork();

	if (frk1 == 0)
	{
		err = execve(argv[0], argv, nwwenviron);
		if (err != 0)
			perror("Couldn't execute");
	}
	else if (frk1 == -1)
	{
		perror("Couldn't fork");
	}
	else
	{
		frkerr = wait(&status);
		if (frkerr == -1)
			perror("Wait error");
	}

	return (0);
}
