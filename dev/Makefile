
CC = gcc
CCX = g++
INCLUDE = -I "./include"
CXXFLAGS = -Wall -g ${INCLUDE}
CFLAGS = -Wall -g ${INCLUDE}

BUILD_DIR = ./build
MYLIB = libpop.a
LIB_OUT = ${BUILD_DIR}/lib/${MYLIB}
LIB_HEADER = POP.h

SRCS = eq_str.c find_next_prime.c hashmap.c linked_list.c
OBJS = ${SRCS:.c=.o}



all: ${LIB_OUT} ./build/include/${LIB_HEADER}

clean:
	rm -rf *.o
	rm -f *.exe

test_hmap: hashmap.o tests/hashmap_test.c
	${CC} ${CFLAGS} tests/hashmap_test.c hashmap.o -o test_hashmap.exe -L ./build/lib/ -lpop
	./test_hashmap.exe

./build/include/${LIB_HEADER}:
	cp ./include/${LIB_HEADER} ./build/include

${LIB_OUT}: ${OBJS}
	ar rc ${LIB_OUT} ${OBJS}

.PHONY: all clean test_hashmap