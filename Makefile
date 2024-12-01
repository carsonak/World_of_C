BINDIR := bin
CC := gcc
STANDARD := --std=c17
WFLAGS := -Wall -Wextra -pedantic -Werror
OPTIMISATION := -Og
DEBUG := -g3 -fno-omit-frame-pointer
SANITIZER := -fsanitize=address -fsanitize=undefined -fno-common -D_FORTIFY_SOURCE=0
CFLAGS = $(STANDARD) $(WFLAGS) $(OPTIMISATION) $(DEBUG) $(SANITIZER)


$(BINDIR)/%: %.c bin
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR):
	mkdir -p $@
