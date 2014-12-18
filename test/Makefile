include ../config.mk

TARGET=out
OBJECTS=main.o test.o list_test.o

%.o : %.cpp
	${CC} -c ${FLAGS} $< -o $@

${TARGET}: ${OBJECTS}
	${CC} ${FLAGS} ${OBJECTS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f *.o out
