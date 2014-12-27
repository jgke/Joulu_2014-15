CXX=g++
CXXFLAGS=-O3 -Wall -Wextra -Wno-unused-parameter \
	 -Wno-missing-field-initializers -I../include
TEX2PDF=texi2pdf -q -c -b
HEADERFILES=common.hpp coord.hpp handle.hpp list.hpp qtree.hpp queue.hp \
	    search.hpp
HEADERS=$(addprefix ../include/, $(HEADERFILES))
LOBJECTFILES=handle.o
LOBJECTS=$(addprefix ../lib/, $(LOBJECTFILES))
.PHONY: config.mk Makefile all clean
