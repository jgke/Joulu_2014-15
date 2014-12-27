include ../config.mk

TARGET=../libtest
OBJECTS=main.o test.o coord_test.o list_test.o qtreenode_test.o qtree_test.o \
	queue_test.o
CXXFLAGS += -O0 -g

%.o : %.cpp ${HEADERS}
	${CXX} -c ${CXXFLAGS} -rdynamic $< -o $@

${TARGET}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -rdynamic ${OBJECTS} ${LOBJECTS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} *.o
