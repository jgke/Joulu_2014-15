TARGET=out
FILES=main.cpp block.cpp
FLAGS=-g
CC=g++
all:
	${CC} ${FLAGS} ${FILES} -o ${TARGET}
