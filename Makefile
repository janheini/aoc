CC = gcc
LINKER = gcc
CFLAGS = -std=c99 -Wall -Wpointer-arith
DEBUG = -g

SOURCES=$(wildcard *.c)
BINARIES=$(SOURCES:.c=)

# disable default suffixes
.SUFFIXES:

%: %.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

all: $(BINARIES)

.PHONY: clean
clean:
	rm -f $(BINARIES)
