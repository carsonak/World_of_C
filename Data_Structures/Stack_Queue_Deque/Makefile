BINDIR := bin
CC := gcc
CFLAGS := --std=c17 -Wall -Wextra -pendantic -Werror -Og -g3 -fsanitize=address -fsanitize=undefined

$(BINDIR)/test_%: test_%.c %.c doubly_linked_list.c singly_linked_list.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@
