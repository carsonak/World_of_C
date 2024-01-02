# Some simple math functions

These functions are not limited to standard C variable sizes.
Compiling commands:
    - Debugging: gcc -std=c17 -lm -lrt -g -pedantic -Wall -Werror -Wextra -fdiagnostics-color=always -fsanitize=undefined -fsanitize-undefined-trap-on-error -fstack-protector-all ./*.c -o ./infiX_math
    - Optimised: gcc -std=c17 -lm -lrt -pedantic -Wall -Werror -Wextra -O3 ./*.c -o ./infiX_math
