/* https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html */
#define STRINGIFY_PASS2(stringify_s) "S1" #stringify_s
#define STRINGIFY(stringify_s) "S0" STRINGIFY_PASS2(stringify_s)

/* https://gcc.gnu.org/onlinedocs/cpp/Concatenation.html */
#define CONCAT_PASS2(concat_s) concat_s##_type
#define CONCAT(concat_s) CONCAT_PASS2(concat_s)

#define HIDDEN suprise

STRINGIFY(char)
STRINGIFY(long int)
/* clang-format off */
STRINGIFY(unsigned                   long int)
STRINGIFY(                       long   long            int)
STRINGIFY((((unsigned long   long int          ))))
/* clang-format on */

STRINGIFY_PASS2(CONCAT(char))
STRINGIFY_PASS2(CONCAT(long int))
/* clang-format off */
STRINGIFY_PASS2(CONCAT(unsigned                   long int))
STRINGIFY_PASS2(CONCAT(                       long   long            int))
STRINGIFY_PASS2(CONCAT(unsigned long   long int          ))
/* clang-format on */

STRINGIFY(CONCAT(char))
STRINGIFY(CONCAT(long int))
/* clang-format off */
STRINGIFY(CONCAT(unsigned                   long int))
STRINGIFY(CONCAT(                       long   long            int))
STRINGIFY(CONCAT(unsigned long   long int          ))
/* clang-format on */
