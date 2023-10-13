### Branching, Merging and Committing Practice

A program used to perform basic calculations shall be used for this
practice project.

#### 1. main.c

##### PURPOSE
- Contains the main function, it accepts arguments at runtime.
- Checks the number of arguments passed is exactly 3
- Checks the supported operations
- Prints results to standard output

The main.c file initially looks like this:

~~~~
#include "calc.h"

/**
 * main - accepts 3 arguments on runtime and executes predefined
 * operations with them.
 * @argc: number of arguments + program name
 * @argv: pointer to strings(the arguments)
 *
 * Return: 0 on success, 98 if number of arguments isn't 3
 * 99 if operand is not found, 100 if dividing or modulus by 0.
 */
int main(int argc, char *argv[])
{
	int a, b;

	if (argc != 4)
	{
		printf("Error\n");
		return (98);
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);
	if (get_op_func(argv[2], a, b) == NULL)
	{
		printf("Error\n");
		return (99);
	}
	else if (get_op_func(argv[2], a, b) == -1)
	{
		printf("Error\n");
		return (100);
	}
	else
		printf("%d\n", get_op_func(argv[2], a, b));

	return (0);
}

~~~~

#### 2. get_op_func.c

##### PURPOSE
- Matches the supported symbols to the right function
- Executes the right function once matched
- Returns the results of the operation
- Returns NULL if no match

The get_op_func.c file initially looks like this:

~~~~
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

~~~~

#### 3. calc.h

##### PURPOSE
- Contains all the function declarations needed and standard library headers

The calc.h file initially looks like this:

~~~~
#ifndef CALC_H_
#define CALC_H_

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
int op_add(int a, int b);
int op_sub(int a, int b);
int op_mul(int a, int b);
int op_div(int a, int b);
int get_op_func(char *s, int num1, int num2);

#endif /*CALC_H_*/

~~~~

#### 4. op_functions.c

##### PURPOSE
- Contains functions for simple calculation
- Should eventually contain the following functions:
    1. int op_add(int a, int b);
    2. int op_sub(int a, int b);
    3. int op_mul(int a, int b);
    4. int op_div(int a, int b);

The op_functions.c file initially looks like this:

~~~~
#include "calc.h"

/**
 * op_add - adds a and b
 * @a: first integer
 * @b: second integer
 *
 * Return: the results of the operation.
 */

/*Place code for addition here*/

/**
 * op_sub - subtracts a from b
 * @a: first integer
 * @b: second integer
 *
 * Return: the results of the operation.
 */

/*Place code for subtraction here*/

/**
 * op_mul - multiplies a by b
 * @a: first integer
 * @b: second integer
 *
 * Return: the results of the operation.
 */

/*Place code for multiplication here*/

/**
 * op_div - divides a by b
 * @a: first integer
 * @b: second integer
 *
 * Return: the results of the operation, -1 if a or b == 0
 */

/*Place code for division here*/

~~~~
