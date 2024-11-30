BINDIR := bin
CC := gcc
STANDARD := --std=c17
WFLAGS := -Wall -Wextra -pedantic -Werror
OPTIMISATION := -Og
DEBUG := -g3
SANITIZER := -fsanitize=address -fsanitize=undefined
CFLAGS = $(STANDARD) $(WFLAGS) $(OPTIMISATION) $(DEBUG) $(SANITIZER)

$(BINDIR)/test_%: test_%.c %.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@
