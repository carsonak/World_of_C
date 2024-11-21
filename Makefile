BINDIR := bin
CC := gcc
CFLAGS := --std=c17 -Wall -Wextra -Werror -Og -g3 -fsanitize=address -fsanitize=undefined


$(BINDIR)/%: %.c bin
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR):
	mkdir -p $@
