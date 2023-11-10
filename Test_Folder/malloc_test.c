#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *array;
	char *str;
	int i = 0;

	array = malloc(sizeof(*array) * strlen(argv[1]));
	str = malloc(sizeof(char) * strlen(argv[2]));

	if (array == NULL || str == NULL)
		return (-1);

	for (i = 0; argv[1][i]; i++)
		array[i] = argv[1][i];

	array[i] = '\0';

	for (i = 0; argv[2][i]; i++)
		str[i] = argv[2][i];

	str[i] = '\0';

	for (i = 0; array[i]; i++)
		printf("[%d]: %c ", i, array[i]);

	printf("\n\n");

	for (i = 0; str[i]; i++)
		printf("[%d]: %c ", i, str[i]);

	printf("\n\n");

	free(array);
	free(str);

	return (0);
}
