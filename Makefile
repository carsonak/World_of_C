BINDIR := bin
CC := clang
C_STANDARD := --std=c17
WFLAGS := -Wall -Wextra -Wformat -Wformat=2 -pedantic -Werror
OPTIMISATION := -Og
DEBUG := -g3 -fno-omit-frame-pointer
SANITIZER := -fsanitize=address -fsanitize=undefined -fno-common
CFLAGS = $(C_STANDARD) $(WFLAGS) $(OPTIMISATION) $(DEBUG) $(SANITIZER)


$(BINDIR)/%: %.c bin
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR):
	mkdir -p $@
