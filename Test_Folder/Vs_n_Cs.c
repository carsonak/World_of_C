#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * vowsncons - counts number of vowels and consonants in a string
 * @str: pointer to string being checked
 */
void vowsncons(char *str)
{
	char *vowels = "aeiouAEIOU";
	bool isVowel;
	int a, b, vows = 0, cons = 0;

	for (a = 0; str[a]; a++)
	{
		if ((str[a] >= 'a' && str[a] <= 'z') || (str[a] >= 'A' && str[a] <= 'Z'))
		{
			for (b = 0; vowels[b]; b++)
			{
				if (str[a] == vowels[b])
				{
					vows++;
					isVowel = true;
					break;
				}
				else
					isVowel = false;
			}

			if (!isVowel)
				cons++;
		}
	}

	if (vows)
		printf("Vowels: %d\n", vows);
	if (cons)
		printf("Consonants: %d\n", cons);
}

/**
 * main - calls vowsncons
 * 
 * Return: always 0.
 */
int main(void)
{
	char *s1 = "Welcome to w3resource.com";

	vowsncons(s1);

	return (0);
}
