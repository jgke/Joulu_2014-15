include config.mk

TARGET=out
OBJECTS=main.o block.o
.PHONY: doc test

%.o : %.cpp
	${CC} -c ${CCFLAGS} $< -o $@

${TARGET}: ${OBJECTS}
	${CC} ${CCFLAGS} ${OBJECTS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f out *.o

doc:
	cd doc; make

test:
	cd test; make
