CC := gcc
CFLAGS := --std=c17 -Wall -Wextra -Werror -Og -g3 -fsanitize=address -fsanitize=undefined

bin/%: %.c bin
	$(CC) $(CFLAGS) $< -o $@

bin:
	mkdir -p bin
