/* https://gcc.gnu.org/onlinedocs/cpp/Self-Referential-Macros.html */
#define MONDAY MONDAY
#define TUESDAY TUESDAY
#define WEDNESDAY WEDNESDAY
#define THURSDAY THURSDAY
#define FRIDAY FRIDAY
#define SATURDAY SATURDAY
#define SUNDAY SUNDAY

/*
If a macro references itself during argument expansion, it will not be
expanded again.
*/
#define x (3 * y)
#define y (2 * x)

/*
These seemingly infinitely recursive macros stop expanding once a
self-reference occurs.
*/
#define QUAD(n) (CUBE(n) * n)
#define CUBE(n) (SQUARE(n) * n)
#define SQUARE(n) (QUAD(n) / n)

enum weekdays
{
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
};
/* clang-format off */
MONDAY
#ifdef MONDAY
left me broken
#endif

x
y

QUAD(2)
CUBE(2)
SQUARE(2)
	/* clang-format on */
