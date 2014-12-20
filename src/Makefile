include ../config.mk

TARGET=../out
OBJECTS=main.o generators/prim.o
LIBS=-lncurses

%.o : %.cpp ${HEADERS}
	${CC} -c ${CCFLAGS} $< -o $@

${TARGET}: ${OBJECTS}
	${CC} ${CCFLAGS} ${OBJECTS} ${LIBS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} *.o
