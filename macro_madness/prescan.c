#define STR_2(str_s) "S0" #str_s
#define STR(str_s) "S1" STR_2(str_s)

#define CAT_2(cat_s) cat_s##_type
#define CAT(cat_s) CAT_2(cat_s)

#define HIDDEN dagger
#define CLOAK STR_2(HIDDEN)
#define DARK STR(HIDDEN)

/* https://gcc.gnu.org/onlinedocs/cpp/Argument-Prescan.html */
/*
Arguments to stringifying and concatenation macros are pasted as is
into the macro body. Therefore calling such macros with macros as arguments
results in the macro name rather than its value in the macro body.
*/
CAT_2(HIDDEN) /* HIDDEN_type */
STR_2(HIDDEN) /* "S0" "HIDDEN" */
/*
To avoid this we define a normal function like macro that calls the corresponding
stringifying/concatenation macro. This allows for the macro arguments to be
fully expanded before being pasted into the macro body. (Which in this case
would result in the fully expanded macro values being pasted as arguments to
the stringifying/concatenation macro).
*/
CAT(HIDDEN) /* CAT(dagger) -> CAT_2(dagger) -> dagger_type */
STR(HIDDEN) /* STR(dagger) -> "S1" STR_2(dagger) -> "S1" "S0" "dagger" */

STR_2(STR_2(3)) /* "S0" "STR_2(3)" */
STR_2(STR(3))   /* "S0" "STR(3)" */
STR(STR_2(3))   /* STR("S0" "3") -> "S1" "\"S0\" \"3\"" */
STR(STR(3))     /* STR("S1" STR_2(3)) -> STR("S1" "S0" "3") -> "S1" STR_2("S1" "S0" "3") -> "S1" "S0" "\"S1\" \"S0\" \"3\""*/

STR_2(CLOAK) /* "S0" "CLOAK" */
STR(CLOAK)   /* STR(STR_2(HIDDEN)) -> STR("S0" "HIDDEN") -> "S1" STR_2("S0" "HIDDEN") -> "S1" "S0" "\"S0\" \"HIDDEN\"" */

STR_2(DARK) /* "S0" "DARK" */
STR(DARK)   /* STR(STR(HIDDEN)) -> STR(STR(dagger)) -> STR("S1" STR_2(dagger)) -> STR("S1" "S0" "dagger") -> "S1" STR_2("S1" "S0" "dagger") -> "S1" "S0" "\"S1\" \"S0\" \"dagger\"" */

STR_2(STR_2(CLOAK))
STR_2(STR(CLOAK))
STR(STR_2(CLOAK))
STR(STR(CLOAK))

STR_2(STR_2(DARK))
STR_2(STR(DARK))
STR(STR_2(DARK))
STR(STR(DARK)) /* STR(STR(STR(HIDDEN))) -> STR(STR(STR(dagger))) -> STR(STR("S1" STR_2(dagger))) -> STR(STR("S1" "S0" "dagger")) -> STR("S1" STR_2("S1" "S0" "dagger")) -> STR("S1" "S0" "\"S1\" \"S0\" \"dagger\"") -> "S1" STR_2("S1" "S0" "\"S1\" \"S0\" \"dagger\"") -> "S1" "S0" \"S1\" \"S0\" \"\\\"S1\\\" \\\"S0\\\" \\\"dagger\\\"\"" */
