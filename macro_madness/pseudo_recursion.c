/* Analysing pseudo-recursion of Macros in C from this S.O. question. */
/* https://stackoverflow.com/a/13459454 */
/* https://github.com/swansontec/map-macro */

/* Used as an invisible token to separate Macro name from parenthesis. */
#define TOKEN_SEPARATOR

/*
When the Macro call expands the invisible token separator gets between the
macro name and the parenthesis and the CPP cannot therefore evaluate the
embedded macro call.
The token separator then evaluates to nothing but it is already too late and
the CPP doesn't evaluate the expansion again.
*/
#define CALL0(x) x CALL1 TOKEN_SEPARATOR(x)
#define CALL1(x) x CALL0 TOKEN_SEPARATOR(x)

CALL0
CALL0("Plain call")

/*
We can trigger another evaluation on the expansion of CALL0(x) by passing it as
an argument to another macro.
https://gcc.gnu.org/onlinedocs/cpp/Argument-Prescan.html
*/
#define EVAL(x) x

/* The more layers we wrap the call in, the more evaluations we get. */
EVAL(CALL0("1-layer"))
EVAL(EVAL(CALL0("2-layers")))
EVAL(EVAL(EVAL(CALL0("3-layers"))))

/*
Evaluations can also be stacked.
Because the initial stack is a layered call we get 1 free evaluation.
*/
#define EVAL_STACK0(...) __VA_ARGS__
#define EVAL_STACK1(...) EVAL_STACK0(__VA_ARGS__)
#define EVAL_STACK2(...) EVAL_STACK1(__VA_ARGS__)

EVAL_STACK1(CALL0("1-stack"))
EVAL_STACK2(CALL0("2-stacks"))

/*
We can then combine layering and stacking to increase the number of
evaluations.
*/
#define EVAL_L2_S0(...) __VA_ARGS__
#define EVAL_L2_S1(...) EVAL_L2_S0(EVAL_L2_S0(__VA_ARGS__))
#define EVAL_L2_S2(...) EVAL_L2_S1(EVAL_L2_S1(__VA_ARGS__))
#define EVAL_L2_S3(...) EVAL_L2_S2(EVAL_L2_S2(__VA_ARGS__))

EVAL_L2_S1(CALL0("2-layers:1-stack"))
EVAL_L2_S2(CALL0("2-layers:2-stacks"))
EVAL_L2_S3(CALL0("2-layers:3-stacks"))

/*
TODO: Derive formula for calculating number of evaluated calls.
*/
#define EVAL_L3_S0(...) __VA_ARGS__
#define EVAL_L3_S1(...) EVAL_L3_S0(EVAL_L3_S0(EVAL_L3_S0(__VA_ARGS__)))
#define EVAL_L3_S2(...) EVAL_L3_S1(EVAL_L3_S1(EVAL_L3_S1(__VA_ARGS__)))
#define EVAL_L3_S3(...) EVAL_L3_S2(EVAL_L3_S2(EVAL_L3_S2(__VA_ARGS__)))

EVAL_L3_S1(CALL0("3-layers:1-stacks"))
EVAL_L3_S2(CALL0("3-layers:2-stacks"))
EVAL_L3_S3(CALL0("3-layers:3-stacks"))
