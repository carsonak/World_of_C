#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHM_SIZE (1024) /*Adjust the size according to your needs*/

int main()
{
	int i = 0, shm_fd = 0;
	pid_t pid = 0;
	const char *shm_name = "/my_shared_memory";
	char *shared_memory = NULL;

	/*Create or open the shared memory segment*/
	shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
	if (shm_fd == -1)
	{
		perror("shm_open");
		exit(EXIT_FAILURE);
	}

	/*Size the shared memory segment*/
	if (ftruncate(shm_fd, SHM_SIZE) == -1)
	{
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}

	/*Map the shared memory segment into the process's address space*/
	shared_memory = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shared_memory == MAP_FAILED)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	/*Fork a child process*/
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		const char *strings[] = {"String1", "String2", "String3", "String4", "String5",
								 "String6", "String7", "String8", "String9", "String10"};

		/*Write strings to shared memory*/
		for (i = 0; i < 10; ++i)
			strcpy(shared_memory + i * 20, strings[i]); /*Assuming each string has a maximum length of 20*/

		exit(EXIT_SUCCESS);
	}
	else
	{
		/*Wait for the child process to complete*/
		wait(NULL);
		printf("Strings in shared memory:\n");
		for (i = 0; i < 10; ++i)
			printf("%s\n", shared_memory + i * 20);

		/*Unmap and close the shared memory segment*/
		if (munmap(shared_memory, SHM_SIZE) == -1)
		{
			perror("munmap");
			exit(EXIT_FAILURE);
		}

		if (close(shm_fd) == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}

		/*Unlink the shared memory segment (optional)*/
		if (shm_unlink(shm_name) == -1)
		{
			perror("shm_unlink");
			exit(EXIT_FAILURE);
		}
	}

	return (0);
}
