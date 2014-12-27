include ../config.mk

OBJECTS=handle.o

%.o : %.cpp ${HEADERS}
	${CC} -c ${CCFLAGS} -rdynamic $< -o $@

all: ${OBJECTS}

clean:
	rm -f ${TARGET} *.o
