TARGET=out
OBJECTS=main.o block.o
FLAGS=-g -Wall
CC=g++
.PHONY: Makefile all clean doc test

%.o : %.cpp
	${CC} -c ${FLAGS} $< -o $@

${TARGET}: ${OBJECTS}
	${CC} ${FLAGS} ${OBJECTS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f out *.o

doc:
	cd doc; make

test:
	cd test; make
