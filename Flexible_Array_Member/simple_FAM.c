#include "FAM.h"

/**
 * main - simple flexible member array
 *
 * Return: 0
 */
int main(void)
{
	char *my_str = "Hello World!";
	struct String *s = malloc(sizeof(*s) + (sizeof(*my_str) * strlen(my_str)) + 1);

	s->len = strlen(my_str) + 1;
	strcpy(s->str, my_str);
	printf("sizeof(s): %zu\n", sizeof(s));
	printf("s->len: %ld\n", s->len);
	printf("s->str: %s\n", s->str);
	free(s);
	return (0);
}
