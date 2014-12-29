include ../config.mk

TARGET=../putkijuoksu
OBJECTS=main.o generator.o ui.o generators/prim.o generators/life.o \
	generators/empty.o
LIBS=-lncurses

%.o : %.cpp ${HEADERS}
	${CXX} -c ${CXXFLAGS} $< -o $@

${TARGET}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LOBJECTS} ${LIBS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} *.o generators/*.o
