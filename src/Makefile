include ../config.mk

TARGET=../out
OBJECTS=main.o block.o

%.o : %.cpp
	${CC} -c ${CCFLAGS} $< -o $@

${TARGET}: ${OBJECTS}
	${CC} ${CCFLAGS} ${OBJECTS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} *.o
