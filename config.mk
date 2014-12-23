CC=g++
CCFLAGS=-O3 -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -I../include
TEX2PDF=texi2pdf -q -c -b
HEADERS=../include/qtree.hpp ../include/list.hpp ../include/coord.hpp ../include/common.hpp
.PHONY: config.mk Makefile all clean
