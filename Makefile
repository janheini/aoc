SOURCES:=$(shell echo *.c)
BINARIES:=$(shell echo $(SOURCES) | tr -d '.c')
CFLAGS=-O2 -march=native

all: $(BINARIES)

day%: day%.c

clean:
	rm -f $(BINARIES)
