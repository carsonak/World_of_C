#include "FAM.h"

/**
 * main - simple flexible member array
 *
 * Return: 0
 */
int main(void)
{
	char my_str[] = "Hello World!";
	struct String *s = malloc(offsetof(typeof(*s), str) + (sizeof(*my_str) * sizeof(my_str)));

	s->len = sizeof(my_str) - 1;
	strcpy(s->str, my_str);
	report(sizeof(s));
	report(s->len);
	printf("s->str: %s\n", s->str);
	free(s);
	return (0);
}
