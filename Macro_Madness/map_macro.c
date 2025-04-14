/* https://stackoverflow.com/a/13459454 */
/* https://github.com/swansontec/map-macro */
/* Separates Macro name from parenthesis */
#define BLANK

/*
The macro body is only scanned once for macros and since `BLANK` is the
only recognisable macro, B(x) is not evaluated and the recursion that results
from it is not triggered.
*/
#define A(x) x B BLANK(x)
#define B(x) x A BLANK(x)

/*
We can trigger another evaluation on the results of A(x) by passing the call as an
argument to EVAL(x).
*/
#define EVAL(x) x

#define E0(...) __VA_ARGS__
#define E1(...) E0(__VA_ARGS__)
#define E(...) E1(__VA_ARGS__)

A(blah)       /* blah B BLANK(blah) -> blah B (blah) */
EVAL(A(blah)) /* EVAL(blah B BLANK(blah)) -> EVAL(blah B (blah)) -> blah B (blah) -> blah blah A BLANK(blah) -> blah blah A (blah) */
/*                                                                                                   ^ This is the last evaluation as `A (blah)` now triggers the recursion check. */
/* The more layers we wrap the call in, the more evaluations we get. */
EVAL(EVAL(EVAL(EVAL(A(blah)))))
E(A(blah))
