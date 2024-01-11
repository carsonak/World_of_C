#include "infix.h"
#define TESTING_OPS

#ifdef TESTING_OPS
/**
 * infiX_op - determines which operation to execute based on the sign
 * @num1: first number
 * @sign: operand
 * @num2: second number
 * @prog: name of the main program
 *
 * Return: 1 on failure, 0 on success
 */
int infiX_op(char *num1, char *sign, char *num2, char *prog)
{
	size_t i = 0;
	uint32_t *n1_arr = NULL, *n2_arr = NULL, *ans_arr = NULL;
	uint8_t *answer = NULL;
	op_func ops[] = {
		{"+", infiX_add},
		/*{"-", infiX_sub},*/
		{"x", infiX_mul},
		/*{"/", infiX_div},*/
		{NULL, NULL},
	};

	for (i = 0; ops[i].sign; i++)
	{
		errno = 0;
		if (ops[i].sign[0] == sign[0])
		{
			/**
			 * Send num1 and num2 to the converters
			 * Offset pointer by number of leading zeros
			 */
			if (num1)
			{
				n1_arr = str_u32((uint8_t *)&num1[pad_char(num1, "0")]);
				if (!n1_arr)
				{
					if (!errno)
						print_help(prog);

					return (EXIT_FAILURE);
				}
			}

			if (num2)
			{
				n2_arr = str_u32((uint8_t *)&num2[pad_char(num2, "0")]);
				if (!n2_arr)
				{
					if (!errno)
						print_help(prog);

					if (n1_arr)
						free(n1_arr);

					return (EXIT_FAILURE);
				}
			}

			ans_arr = ops[i].f(n1_arr, n2_arr);
			break;
		}
	}

	/**
	 * if (remain)
	 * free(remain);
	 */

	if (n1_arr)
		free(n1_arr);

	if (n2_arr)
		free(n2_arr);

	if (ans_arr)
	{
		answer = u32_str(ans_arr);
		free(ans_arr);
		if (answer)
			printf("%s\n", (char *)&answer[pad_char((char *)answer, "0")]);
		else
			return (EXIT_FAILURE);

		free(answer);
		return (EXIT_SUCCESS);
	}
	else if (!ops[i].sign)
		print_help(prog);

	return (EXIT_FAILURE);
}
#else
/**
 * infiX_op - determines which operation to execute based on the sign
 * @num1: first number
 * @num2: second number
 * @sign: operand
 * @prog: name of this program
 *
 * Return: 1 on failure, 0 on success
 */
int infiX_op(uint8_t *num1, uint8_t *num2, char *sign, char *prog)
{
	size_t i = 0;
	uint8_t *answer = NULL;
	op_func ops[] = {
		{"+", infiX_add},
		{"-", infiX_sub},
		{"x", infiX_mul},
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
		printf("%s\n", (char *)(&answer[pad_char((char *)answer, "0")]));
		free(answer);
		free(remain);
		return (EXIT_SUCCESS);
	}
	else if (!ops[i].sign)
		print_help(prog);

	free(remain);
	return (EXIT_FAILURE);
}
#endif
/**
 * print_help - print help
 * @prog_name: name of this program
 */
void print_help(char *prog_name)
{
	fprintf(stderr, "USAGE: %s <num1> <operand> <num2>\n", prog_name);
	fprintf(stderr, "Only base 10 numbers are currently supported.\n");
	fprintf(stderr, "Currently supported operands are '+', '-', 'x' and '/'.\n");
}
