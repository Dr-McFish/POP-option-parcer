# Makefile for the demo ONLY! not the library itself (check dev folder)

CC = gcc
INCLUDE = -I "build/include"
LDFLAGS = -L "build/lib" 
CFLAGS = -Wall -g ${INCLUDE}

SRCS = POP_example_usage.c
OBJS = ${SRCS:.c=.o}

TEST_PROGRAM = demo.out

all: ${TEST_PROGRAM}

demo: all
	clear
	echo -e "\n\n\n\nFor full usage, check ${TEST_PROGRAM} --help\nExample Usage:"
	./${TEST_PROGRAM} --name Bob --age 25 -n 6 aplles --hate-onions --message "What's up" -sc bananas oranges

clean:
	rm -rf *.o
	rm -f *.exe

${TEST_PROGRAM}: ${OBJS} build/include/POP/POP.h build/lib/libpop.a
	#if this doesn't work, please make sure that the library is compiled using th Makefile in ./dev
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS} -lpop

.PHONY: all demo clean