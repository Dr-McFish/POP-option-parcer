# Main Makefile

CC = gcc
INCLUDE = -I "./include"
CFLAGS = -Wall ${INCLUDE}

BUILD_DIR = ./build
MYLIB = libpop
STATIC_LIB_OUT = ${BUILD_DIR}/lib/${MYLIB}.a
LIB_HEADER = POP.h

SRCS = eq_str.c prime.c hashmap.c linked_list.c POP.c
OBJS = ${SRCS:.c=.o}

debug: debug_set_flags all

release: clean release_set_flags all
	cp -rf build ../
	make clean

all: all_dirs ${STATIC_LIB_OUT} ./build/include/POP/${LIB_HEADER}

clean:
	rm -rf *.o
	rm -f *.exe

test_hmap: tests/hashmap_test.c ${STATIC_LIB_OUT}
	${CC} ${CFLAGS} tests/hashmap_test.c hashmap.o -o test_hashmap.exe -L ./build/lib/ -static -${MYLIB:lib=l}
	./test_hashmap.exe

test_prime: tests/test_prime.c ${STATIC_LIB_OUT}
	${CC} ${CFLAGS} tests/test_prime.c -o test_prime.exe -L ./build/lib/ -lpop
	./test_prime.exe

./build/include/POP/${LIB_HEADER}: ./include/${LIB_HEADER} ./build/include/POP
	cp ./include/${LIB_HEADER} ./build/include/POP/${LIB_HEADER}

${STATIC_LIB_OUT}: ${OBJS}
	ar rcs $@ ${OBJS}

./build:
	mkdir $@

./build/include: ./build
	mkdir $@

./build/include/POP: ./build/include
	mkdir $@

./build/lib: ./build
	mkdir $@

all_dirs: ./build/include/POP ./build/lib

debug_set_flags:
	$(eval CFLAGS += -g)

release_set_flags:
	$(eval CFLAGS += -O3)

.PHONY: release debug all clean test_hashmap debug_set_flags release_set_flags all_dirs