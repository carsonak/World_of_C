#include <string.h>
#include <stdio.h>

char *_strtok(char *str, const char *delim);
unsigned int _strspn(char *s, char *accept);
unsigned long int _strlen(char *s);

/**
 * main - testing strtok
 *
 * Return: 0
 */
int main(void)
{
	char *tok1, *tok2;
	char str1[] = " ,./qwert yu./iop/ asdfg,";
	char str2[] = " ,./qwert yu./iop/ asdfg,";

	tok1 = strtok(str1, " ,./");
	printf("S: %s\n", tok1);
	tok2 = _strtok(str2, " ,./");
	printf("C: %s\n\n", tok2);

	while (tok1 && tok2)
	{
		tok1 = strtok(NULL, " ,./");
		printf("S: %s\n", tok1);
		tok2 = _strtok(NULL, " ,./");
		printf("C: %s\n\n", tok2);
	}

	return (0);
}

/**
 * _strtok - breaks a string into sections
 * @str: the string
 * @delim: the delimeter
 *
 * Return: pointer to the tokenised string
 */
char *_strtok(char *str, const char *delim)
{
	static char *tok_ptr;
	static long int str_len;
	char *tok_b;
	unsigned int i = 0;

	if (str)
	{
		tok_ptr = str;
		str_len = _strlen(tok_ptr);
	}

	tok_ptr = &tok_ptr[_strspn(tok_ptr, delim)];
	tok_b = tok_ptr;

	while (str_len > 0)
	{
		for (i = 0; delim[i]; i++)
		{
			if (*tok_ptr == delim[i])
			{
				*tok_ptr = '\0';
				break;
			}
		}

		tok_ptr++;
		str_len--;
		if (delim[i])
			break;
	}

	if (str_len <= 0)
		tok_b = NULL;

	return (tok_b);
}

/**
 *_strspn - checks for similar characters in different strings
 *@s: String to be checked
 *@accept: the check string
 *
 *Return: the total size of checked strings.
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int i, j, b, a = 0;

	for (i = 0; s[i]; i++)
	{
		b = a;
		for (j = 0; accept[j]; j++)
			if (accept[j] == s[i])
				a++;

		if ((accept[j] == '\0') && (a - b == 0))
			break;
	}

	return (a);
}

/**
 *_strlen - prints string length.
 *@s: string
 *
 *Return: lenth of the string
 */
unsigned long int _strlen(char *s)
{
	unsigned long int cnt;

	for (cnt = 0; s[cnt]; cnt++)
		;

	return (cnt);
}
