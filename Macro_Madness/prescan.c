#define STRINGIFY_PASS2(stringify_s) "S1" #stringify_s
#define STRINGIFY(stringify_s) "S0" STRINGIFY_PASS2(stringify_s)

#define CONCAT_PASS2(concat_s) concat_s##_type
#define CONCAT(concat_s) CONCAT_PASS2(concat_s)

#define HIDDEN suprise

/* https://gcc.gnu.org/onlinedocs/cpp/Argument-Prescan.html */
/*
Arguments to stringifying and concatenation macros are pasted as is
into the macro body. Therefore calling such macros with macros as arguments
results in the macro name rather than its value in the macro body.
*/
CONCAT_PASS2(HIDDEN)
STRINGIFY_PASS2(HIDDEN)
/*
To avoid this we define a normal function like macro that calls the corresponding
stringifying/concatenation macro. This allows for the macro arguments to be
fully expanded before being pasted into the macro body. (Which in this case
would result in the fully expanded macro values being pasted as arguments to
the stringifying/concatenation macro).
*/
CONCAT(HIDDEN)
STRINGIFY(HIDDEN)

STRINGIFY_PASS2(STRINGIFY_PASS2(3))
STRINGIFY(STRINGIFY_PASS2(3)) /* -> "S0" STRINGIFY_PASS2(STRINGIFY_PASS2(3)) -> "S0" STRINGIFY_PASS2("S1" "3") -> "S0" "S1" "\"S1\" \"3\""*/
STRINGIFY_PASS2(STRINGIFY(3))
