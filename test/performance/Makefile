include ../../config.mk

TARGET=performance-test
OBJECTS=main.o
CXXFLAGS+= -I../../include
IMAGES=qtree-add.png qtree-contains.png qtree-get.png qtree-map.png

%.o : %.cpp ${HEADERS}
	${CXX} -c ${CXXFLAGS} $< -o $@

%.png : %.dat
	gnuplot $*.gp > ../../doc/performance/$@ 2> /dev/null

.PRECIOUS: %.dat
%.dat : ${TARGET}
	./${TARGET}

all: ${TARGET} ${IMAGES}

${TARGET}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${TARGET}

clean:
	rm -rf ${TARGET} *.png *.dat *.o
