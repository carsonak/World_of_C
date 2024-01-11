#ifndef _INFIX_H_
#define _INFIX_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <math.h> /*pow(), Need to link with -lm*/

/*Max nnumber of digits for uint32_t*/
#define U32_DIGITS (9)

/*Max size for uint32_t calculations: 10^9*/
#define U32_ROLL (1000000000)

/*Max nnumber of digits for uint64_t*/
#define U64_DIGITS (U32_DIGITS * U32_DIGITS)

/*Max size for uint64_t calculations: 10^18*/
#define U64_ROLL (U32_ROLL * U32_ROLL)

/*A dynamically allocated buffer to store the remainder of division*/
extern uint8_t *remain;

/**
 * struct operations - a structure of an operation and it's function
 * @sign: the operation
 * @f: a pointer to the corresponding function
 */
typedef struct operations
{
	char *sign;
	uint32_t *(*f)(uint32_t *n1, uint32_t *n2);

} op_func;

void print_help(char *prog_name);
int infiX_op(char *num1, char *sign, char *num2, char *prog);
uint32_t *str_u32(uint8_t *num);
uint8_t *u32_str(uint32_t *u32a);
uint8_t *infiX_div(uint8_t *dividend, uint8_t *divisor);
uint8_t *infiX_sub(uint8_t *n1, uint8_t *n2);
uint32_t *infiX_mul(uint32_t *n1_arr, uint32_t *n2_arr);
uint32_t *infiX_add(uint32_t *n1_arr, uint32_t *n2_arr);
size_t pad_char(char *str, char *ch);
size_t strtonul(char *num, size_t nelem);
void *memfill(void *mem, char b, size_t start, size_t nbytes);

#endif /*_INFIX_H_*/
