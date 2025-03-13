#include <stdio.h>

/* https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html */
#define STRINGIFY_PASS2(stringify_s) #stringify_s
#define STRINGIFY(stringify_s) STRINGIFY_PASS2(stringify_s)

/* https://gcc.gnu.org/onlinedocs/cpp/Concatenation.html */
#define CONCAT(concat_s) concat_s##_type

int main(void)
{
	printf(STRINGIFY(char) "\n");
	printf(STRINGIFY(int) "\n");
	printf(STRINGIFY(float) "\n");
	printf(STRINGIFY(double) "\n");
	printf(STRINGIFY(long) "\n");
	printf(STRINGIFY(signed char) "\n");
	printf(STRINGIFY(unsigned int) "\n");
	printf(STRINGIFY(long int) "\n");
	/* clang-format off */
	printf(STRINGIFY(unsigned                   long int) "\n");
	printf(STRINGIFY(                       long   long            int) "\n");
	printf(STRINGIFY((((unsigned long   long int          )))) "\n");
	/* clang-format on */

	printf("\n");

	printf(STRINGIFY_PASS2(CONCAT(char)) "\n");
	printf(STRINGIFY_PASS2(CONCAT(int)) "\n");
	printf(STRINGIFY_PASS2(CONCAT(float)) "\n");
	printf(STRINGIFY_PASS2(CONCAT(double)) "\n");
	printf(STRINGIFY_PASS2(CONCAT(long)) "\n");
	printf(STRINGIFY_PASS2(CONCAT(signed char)) "\n");
	printf(STRINGIFY_PASS2(CONCAT(unsigned int)) "\n");
	printf(STRINGIFY_PASS2(CONCAT(long int)) "\n");
	/* clang-format off */
	printf(STRINGIFY_PASS2(CONCAT(unsigned                   long int)) "\n");
	printf(STRINGIFY_PASS2(CONCAT(                       long   long            int)) "\n");
	printf(STRINGIFY_PASS2(CONCAT(unsigned long   long int          )) "\n");
	/* clang-format on */

	printf("\n");

	printf(STRINGIFY(CONCAT(char)) "\n");
	printf(STRINGIFY(CONCAT(int)) "\n");
	printf(STRINGIFY(CONCAT(float)) "\n");
	printf(STRINGIFY(CONCAT(double)) "\n");
	printf(STRINGIFY(CONCAT(long)) "\n");
	printf(STRINGIFY(CONCAT(signed char)) "\n");
	printf(STRINGIFY(CONCAT(unsigned int)) "\n");
	printf(STRINGIFY(CONCAT(long int)) "\n");
	/* clang-format off */
	printf(STRINGIFY(CONCAT(unsigned                   long int)) "\n");
	printf(STRINGIFY(CONCAT(                       long   long            int)) "\n");
	printf(STRINGIFY(CONCAT(unsigned long   long int          )) "\n");
	/* clang-format on */
	return (0);
}
