include ../config.mk

TARGET=../putkijuoksu
OBJECTS=main.o generator.o generators/prim.o generators/life.o generators/empty.o
LIBS=-lncurses

%.o : %.cpp ${HEADERS}
	${CC} -c ${CCFLAGS} $< -o $@

${TARGET}: ${OBJECTS}
	${CC} ${CCFLAGS} ${OBJECTS} ${LIBS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} *.o generators/*.o
