#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * rand_str - generate a string of random characters of a given size.
 * @dest: pointer to a memory location to store the string.
 * @len: number of characters to generate, must be less than sizeof dest.
 * @randint_generator: pointer to a random number generator.
 *
 * Return: pointer to dest.
 */
char *rand_str(char *dest, size_t len, int (*randint_generator)(void))
{
	const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	size_t r = 0;

	while (len--)
	{
		/*What happens when randint_generator always produces numbers less than*/
		/*total number of characters in the selection pool?*/
		r = (size_t)randint_generator() % (sizeof(charset) - 1);
		*dest = charset[r];
		++(dest);
	}

	*dest = '\0';
	return (dest);
}

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(void)
{
	char str[1024];

	str[0] = '\0';
	srand(time(NULL));
	rand_str(str, sizeof(str) - 1, rand);
	printf("%.1024s\n", str);
}
