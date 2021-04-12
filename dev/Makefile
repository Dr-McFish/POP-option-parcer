
CC = gcc
CCX = g++
INCLUDE = -I "./include"
CXXFLAGS = -Wall -g ${INCLUDE}
CCFLAGS = ${CXXFLAGS}

BUILD_DIR = ./build
MYLIB = libpop.a
LIB_OUT = ${BUILD_DIR}/lib/${MYLIB}
LIB_HEADER = POP.h

SRCS = libfile.c
OBJS = ${SRCS:.c=.o}



all: ${LIB_OUT} ./build/include/${LIB_HEADER}

clean:
	rm -rf *.o

./build/include/${LIB_HEADER}:
	cp ./include/${LIB_HEADER} ./build/include

${LIB_OUT}: ${OBJS}
	ar rc ${LIB_OUT} ${OBJS}

.PHONY: all clean