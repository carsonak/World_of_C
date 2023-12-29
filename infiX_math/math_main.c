#include "infix.h"

uint8_t *remain;

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: pointer to an array of strings
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	errno = 0;
	if (argc != 4 || strlen(argv[2]) != 1)
	{
		print_help(argv[0]);
		return (EXIT_FAILURE);
	}
	else if (!isdigit(argv[1][0]) || !isdigit(argv[3][0]))
	{
		fprintf(stderr, "Insufficient digits\n");
		return (EXIT_FAILURE);
	}

	remain = calloc(sizeof(*remain), 150);
	if (!remain)
	{
		perror("Malloc fail");
		return (EXIT_FAILURE);
	}

	return (which_op((uint8_t *)argv[1], (uint8_t *)argv[3], argv[2], argv[0]));
}

/**
 * which_op - determines which operation to execute based on the sign
 * @num1: first number
 * @num2: second number
 * @sign: operand
 * @prog: name of this program
 *
 * Return: 1 on failure, 0 on success
 */
int which_op(uint8_t *num1, uint8_t *num2, char *sign, char *prog)
{
	size_t i = 0, off_set = 0;
	uint8_t *answer = NULL;
	op_func ops[] = {
		{"+", infiX_add},
		{"-", infiX_sub},
		{"*", infiX_mul},
		{"/", infiX_div},
		{NULL, NULL},
	};

	for (i = 0; ops[i].sign; i++)
	{
		if (ops[i].sign[0] == sign[0])
		{
			answer = ops[i].f(num1, num2);
			break;
		}
	}

	if (answer)
	{
		off_set = pad_char((char *)answer, "0");
		printf("%s %s %s = %s\n", (char *)num1, sign, (char *)num2, (char *)(&answer[off_set]));
		free(remain);
		free(answer);
		return (EXIT_SUCCESS);
	}
	else if (!answer && errno)
		perror("FAILED");
	else if (!answer && !ops[i].sign)
		print_help(prog);

	free(remain);
	return (EXIT_FAILURE);
}

/**
 * print_help - print help
 * @prog_name: name of this program
 */
void print_help(char *prog_name)
{
	fprintf(stderr, "USAGE: %s <num1> <operand> <num2>\n", prog_name);
	fprintf(stderr, "Currently supported operands +, -, *, /\n");
	fprintf(stderr, "You might have to escape '*' like this \\*\n");
	fprintf(stderr, "Only base 10 numbers are currently supported\n");
}
