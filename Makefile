BINDIR := bin
CC := gcc
STANDARD := --std=c17
WFLAGS := -Wall -Wextra -pedantic -Werror
OPTIMISATION := -Og
DEBUG := -g3
SANITIZER := -fsanitize=address -fsanitize=undefined
CFLAGS = $(STANDARD) $(WFLAGS) $(OPTIMISATION) $(DEBUG) $(SANITIZER)


$(BINDIR)/%: %.c bin
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR):
	mkdir -p $@
