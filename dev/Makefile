
CC = gcc
CCX = g++
INCLUDE = -I "./include"
CXXFLAGS = -Wall ${INCLUDE}
CFLAGS = -Wall ${INCLUDE}

BUILD_DIR = ./build
MYLIB = libpop.a
LIB_OUT = ${BUILD_DIR}/lib/${MYLIB}
LIB_HEADER = POP.h

SRCS = eq_str.c prime.c hashmap.c linked_list.c POP.c
OBJS = ${SRCS:.c=.o}

release: clean release_set_flags all
	cp -rf build ../
	make clean

debug: debug_set_flags all

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

debug_set_flags:
	$(eval CFLAGS += -g)

release_set_flags:
	$(eval CFLAGS += -O3)

.PHONY: release debug all clean test_hashmap debug_set_flags release_set_flags