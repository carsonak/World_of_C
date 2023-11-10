#include <stdio.h>

/**
 *is_prime_helper - entry function
 * @n : number to check if it is a prime number
 * @divide: checking if it is a divisor of n
 * Return: the prime number
 */
int is_prime_helper(int n, int divide)
{
	if (n < 2)
		return (0);

	if (divide * divide > n)
		return (1);
	else if (n % divide == 0)
		return (0);

	return (is_prime_helper(n, divide + 1));
}
/**
 * is_prime_number - entry function
 * @n: prime number
 * Return: prime number
 */
int is_prime_number(int n)
{

	return (is_prime_helper(n, 2));
}

int main(void)
{
	int r;

	r = is_prime_number(1);
	printf("%d\n", r);
	r = is_prime_number(1024);
	printf("%d\n", r);
	r = is_prime_number(16);
	printf("%d\n", r);
	r = is_prime_number(17);
	printf("%d\n", r);
	r = is_prime_number(25);
	printf("%d\n", r);
	r = is_prime_number(-1);
	printf("%d\n", r);
	r = is_prime_number(113);
	printf("%d\n", r);
	r = is_prime_number(7919);
	printf("%d\n", r);
	r = is_prime_number(2);
	printf("%d\n", r);
	return (0);
}
