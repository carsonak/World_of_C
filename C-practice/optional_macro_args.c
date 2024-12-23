#include <stdio.h>

#define TERM_RESET "\033[0m"
#define TERM_BOLD "\033[1m"
#define TERM_ITALIC "\033[3m"

typedef enum
{
	PLAIN,
	BOLD,
	ITALIC
} txt_style;

/*!
 * @brief prints stylised message.
 * @param message pointer to the message to print.
 * @param line_num line number.
 * @param s style to use.
 */
void print_line(const char *const message, const unsigned long int line_num, const txt_style s)
{
	if (!message)
		return;

	switch (s)
	{
	case PLAIN:
		printf("L%lu: %s\n", line_num, message);
		break;
	case BOLD:
		printf(TERM_BOLD "L%lu: %s\n" TERM_RESET, line_num, message);
		break;
	case ITALIC:
		printf(TERM_ITALIC "L%lu: %s\n" TERM_RESET, line_num, message);
		break;
	default:
		break;
	}
}

#define PRINT_LINE_1_ARGS(message) print_line(message, 0, PLAIN)
#define PRINT_LINE_2_ARGS(message, line_num) print_line(message, line_num, PLAIN)
#define PRINT_LINE_3_ARGS(message, line_num, style) print_line(message, line_num, style)

#define COUNT_VARIABLE_ARGS(arg1, arg2, arg3, func, ...) func

/*https://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros/3048361#3048361*/
/* When `__VA_ARGS__` is expanded, the other arguments will be offset
to the right, allowing us to grab the correct macro at the 4th position. */
#define PRINT_LINE(...)                                          \
	COUNT_VARIABLE_ARGS(__VA_ARGS__, PRINT_LINE_3_ARGS,          \
						PRINT_LINE_2_ARGS, PRINT_LINE_1_ARGS, 0) \
	(__VA_ARGS__)

/*!
 * @brief entry point.
 * @return 0 always.
 */
int main(void)
{
	PRINT_LINE("Hello, World!");
	PRINT_LINE("Hello, World!", __LINE__);
	PRINT_LINE("Hello, World!", __LINE__, ITALIC);

	return (0);
}
