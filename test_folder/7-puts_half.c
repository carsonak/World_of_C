#include "main.h"

void puts_half(char *str)
{
	int i, n, max_str;

	max_str = _strlen(str);
	if (max_str % 2 == 0)
	{
		for (i = max_str / 2; i < max_str; i++)
			putchar(*(str + i));
		putchar('\n');
	}
	else
	{
		n = (max_str - 1) / 2;
		for (i = max_str - n; i < max_str; i++)
			putchar(*(str + i));
		putchar('\n');
	}
}

int _strlen(char *arr)
{
	int i, cnt = 0;

	for (i = 0; arr[i] != '\0'; i++)
		cnt++;

	return (cnt);
}

/**
 * main - check the code for Holberton School students.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *str2 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
	char *str = "Holberton!";

	puts_half(str);
	puts_half(str2);

	return (0);
}
