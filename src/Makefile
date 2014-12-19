include ../config.mk

TARGET=../out
OBJECTS=main.o

%.o : %.cpp
	${CC} -c ${CCFLAGS} $< -o $@

${TARGET}: ${OBJECTS} ${HEADERS}
	${CC} ${CCFLAGS} ${OBJECTS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} *.o
