
CC = gcc
CCX = g++
INCLUDE = -I "./include"
CXXFLAGS = -Wall -g ${INCLUDE}
CFLAGS = -Wall -g ${INCLUDE}

BUILD_DIR = ./build
MYLIB = libpop.a
LIB_OUT = ${BUILD_DIR}/lib/${MYLIB}
LIB_HEADER = POP.h

SRCS = eq_str.c prime.c hashmap.c linked_list.c POP.c
OBJS = ${SRCS:.c=.o}



all: ${LIB_OUT} ./build/include/${LIB_HEADER}

clean:
	rm -rf *.o
	rm -f *.exe

test_hmap: tests/hashmap_test.c ${LIB_OUT}
	${CC} ${CFLAGS} tests/hashmap_test.c hashmap.o -o test_hashmap.exe -L ./build/lib/ -lpop
	./test_hashmap.exe

test_prime: tests/test_prime.c ${LIB_OUT}
	${CC} ${CFLAGS} tests/test_prime.c -o test_prime.exe -L ./build/lib/ -lpop
	./test_prime.exe

./build/include/${LIB_HEADER}: ./include/${LIB_HEADER}
	cp ./include/${LIB_HEADER} ./build/include/POP/${LIB_HEADER}

${LIB_OUT}: ${OBJS}
	ar rc ${LIB_OUT} ${OBJS}

.PHONY: all clean test_hashmap