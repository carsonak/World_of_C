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
