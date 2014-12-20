include ../config.mk

TARGET=../out
OBJECTS=main.o generators/prim.o

%.o : %.cpp ${HEADERS}
	${CC} -c ${CCFLAGS} $< -o $@

${TARGET}: ${OBJECTS}
	${CC} ${CCFLAGS} ${OBJECTS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} *.o
