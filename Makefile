TARGET=out
FILES=main.cpp block.cpp
FLAGS=-g -Wall
CC=g++
all:
	${CC} ${FLAGS} ${FILES} -o ${TARGET}

doc:
	cd doc; make

test:
	cd test; make
