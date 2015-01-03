include ../config.mk

TARGET=../putkijuoksu
OBJECTS=main.o cube.o generator.o resource.o ui.o generators/prim.o \
	generators/life.o generators/empty.o
LIBS=-lm -lSDL2 -lGL -lGLU

%.o : %.cpp ${HEADERS}
	${CXX} -c ${CXXFLAGS} $< -o $@

${TARGET}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LOBJECTS} ${LIBS} -o ${TARGET}

all: ${TARGET}

clean:
	rm -f ${TARGET} *.o generators/*.o
