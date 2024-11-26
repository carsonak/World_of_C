CC := gcc
CFLAGS := --std=c17 -Wall -Wextra -Werror -Og -g3 -fsanitize=address -fsanitize=undefined

bin/test_%: test_%.c %.c doubly_linked_list.c singly_linked_list.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@
