MAKEFLAGS += -s

CC = clang
INCLUDE_PATH = $(shell pwd)/../include
export LD_LIBRARY_PATH = $(shell pwd)/../lib
LIB_NAME = tashi-vertex

examples: quickstart

%: %.c
	$(CC) -L$(LD_LIBRARY_PATH) -l$(LIB_NAME) -I$(INCLUDE_PATH) -o $@ $@.c

run-%: %
	./$(basename $*)
