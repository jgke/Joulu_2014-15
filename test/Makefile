include ../config.mk

TARGET=../libtest
OBJECTS=main.o test.o coord_test.o list_test.o qtreenode_test.o qtree_test.o \
	queue_test.o
CXXFLAGS += -O0 -g -fprofile-arcs -ftest-coverage --coverage -fno-inline \
	    -fno-inline-small-functions -fno-default-inline

%.o : %.cpp ${HEADERS}
	${CXX} -c ${CXXFLAGS} -rdynamic $< -o $@

${TARGET}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -rdynamic ${OBJECTS} ${LOBJECTS} -o ${TARGET}

all: ${TARGET}

coverage: ${TARGET}
	../libtest > /dev/null; \
	    gcov -r -b *.cpp *.hpp > /dev/null; \
	    lcov -c -q -d . -d ../include -o coverage-out --no-external 2> /dev/null; \
	    genhtml -q coverage-out -o ../doc/coverage

clean:
	rm -rf ${TARGET} *.o *.gcda *.gcno *.gcov coverage-out ../doc/coverage
