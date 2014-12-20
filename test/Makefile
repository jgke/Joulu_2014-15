include ../config.mk

TARGET=../out-test
OBJECTS=main.o test.o list_test.o qtreenode_test.o qtree_test.o

%.o : %.cpp ${HEADERS}
	${CC} -c ${CCFLAGS} -rdynamic $< -o $@

${TARGET}: ${OBJECTS}
	${CC} ${CCFLAGS} -rdynamic ${OBJECTS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} *.o
