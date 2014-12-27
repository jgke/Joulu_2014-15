include ../config.mk

TARGET=../libtest
OBJECTS=main.o test.o coord_test.o list_test.o qtreenode_test.o qtree_test.o queue_test.o
CCFLAGS += -O0 -g

%.o : %.cpp ${HEADERS}
	${CC} -c ${CCFLAGS} -rdynamic $< -o $@

${TARGET}: ${OBJECTS}
	${CC} ${CCFLAGS} -rdynamic ${OBJECTS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} *.o
