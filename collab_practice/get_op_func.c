#include "calc.h"

/**
 * get_op_func - finds the right function to execute based on the
 * operator in s, then executes it.
 * @s: operator
 * @num1: left hand integer
 * @num2: right hand integer
 *
 * Return: results of the calculation, NULL if operator doesn't match
 */
int get_op_func(char *s, int num1, int num2)
{

	if (!strcmp(s, "+"))
		return (op_add(num1, num2));
	else if (!strcmp(s, "-"))
		return (op_sub(num1, num2));
	else if (!strcmp(s, "*"))
		return (op_mul(num1, num2));
	else if (!strcmp(s, "/"))
		return (op_div(num1, num2));

	return (NULL);
}
