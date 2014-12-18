include config.mk

.PHONY: prog doc test

all: prog test

clean:
	cd src; make clean
	cd doc; make clean
	cd test; make clean

prog:
	cd src; make

doc:
	cd doc; make

test:
	cd test; make
