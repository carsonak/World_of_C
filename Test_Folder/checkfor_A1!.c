#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int checkfor(char *str);
char *alloc_mem(int arg, char **arr);

/**
 * alloc_mem - allocates appropriate memory to store a series of strings
 * @arg: number of strings passed.
 * @arr: an array of the strings.
 *
 * Return: NULL if fail, pointer to an array of pointers.
 */
char *alloc_mem(int arg, char **arr)
{
	unsigned long int a1, arr_size = 0;
	char *str;

	/*Calculates the size of each string in arr and adds to total array size*/
	for (a1 = 1; a1 < (unsigned long int)arg; a1++)
		arr_size += sizeof(arr[a1]);

	str = malloc(arr_size);
	if (str == NULL)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

/**
 * checkfor - counts the letters, numbers and special characters present in string.
 * @str: string to be checked
 *
 * Return: 1 if no string, 0 on success.
 */
int checkfor(char *str)
{
	unsigned int a = 0, alpha_count = 0, num_count = 0, spec_count = 1;
	bool alpha = false, dig = false, spec = false;

	if (str == NULL)
	{
		printf("No string to check\n");
		return (1);
	}

	while (str[a] != '\0')
	{
		if ((str[a] >= 'a' && str[a] <= 'z') || (str[a] >= 'A' && str[a] <= 'Z'))
		{
			alpha = true;
			alpha_count++;
		}
		else if (str[a] >= 48 && str[a] <= 57)
		{
			dig = true;
			num_count++;
		}
		else if (str[a] >= '\0' || str[a] >= ' ' || str[a] == '\n' || str[a] == '\t' || (str[a] >= '!' && str[a] <= '/') || (str[a] >= ':' && str[a] <= '@') || (str[a] >= '[' && str[a] <= '`') || (str[a] >= '{' && str[a] <= '~'))
		{
			spec = true;
			spec_count++;
		}
		a++;
	}

	if (alpha)
		printf("Number of Alphabets in the string is : %d\n", alpha_count);

	if (dig)
		printf("Number of Digits in the string is : %d\n", num_count);

	if (spec)
		printf("Number of Special characters in the string is : %d\n", spec_count);

	if (!(spec) && !(dig) && !(alpha))
	{
		printf("No string to check\n");
		return (1);
	}

	return (0);
}

/**
 * main - accepts string aguments and calls check for.
 * @ac: number of arguments passed.
 * @av: array of strings
 *
 * Return: 0 if successful, 1 for malloc failure.
 */
int main(int ac, char *av[])
{
	char *string;
	int i;

	if (ac < 2)
	{
		string = "";
		checkfor(string);
	}
	else if (ac == 2)
	{
		string = av[1];
		checkfor(string);
	}
	else
	{
		string = alloc_mem(ac, av);

		if (string == NULL)
		{
			printf("Malloc failure");
			return (1);
		}

		for (i = 1; i < ac; i++)
			strcat(string, av[i]);

		checkfor(string);
		free(string);
	}

	return (0);
}
