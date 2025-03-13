BINDIR := bin
CC := clang
STANDARD := --std=c17
WFLAGS := -Wall -Wextra -Wformat -Wformat=2 -pedantic -Werror
OPTIMISATION := -Og
DEBUG := -g3 -fno-omit-frame-pointer
SANITIZER := -fsanitize=address -fsanitize=undefined -fno-common
CFLAGS = $(STANDARD) $(WFLAGS) $(OPTIMISATION) $(DEBUG) $(SANITIZER)


$(BINDIR)/%: %.c bin
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR):
	mkdir -p $@
