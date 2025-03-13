#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char buf[1024] = {'\0'};

	if (argc < 2)
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);

	fp = fopen(argv[1], "r");
	if (!fp)
	{
		fclose(fp);
		return (EXIT_FAILURE);
	}

	if (fseek(fp, -20, SEEK_END) < 0)
	{
		fclose(fp);
		return (EXIT_FAILURE);
	}

	if (!fread(buf, sizeof(char), 15, fp))
	{
		fclose(fp);
		return (EXIT_FAILURE);
	}

	fclose(fp);
	if (!fwrite(buf, sizeof(char), 20, stdout))
		return (EXIT_FAILURE);

	putchar('\n');
	return (EXIT_SUCCESS);
}
