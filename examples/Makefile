MAKEFLAGS += -s

CC = clang
CFLAGS = -I$(shell pwd)/../include -I$(shell pwd)/include
export LD_LIBRARY_PATH = $(shell pwd)/../lib
LIB_NAME = tashi-vertex

examples: quickstart key-generate key-parse

%: %.c
	$(CC) -L$(LD_LIBRARY_PATH) -l$(LIB_NAME) $(CFLAGS) -o $@ $@.c

run-%: %
	./$(basename $*) $(ARGS)
