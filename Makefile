include config.mk

.PHONY: putkijuoksu doc test

all: putkijuoksu test

clean:
	cd src; make clean
	cd doc; make clean
	cd test; make clean

putkijuoksu:
	cd src; make

doc:
	cd doc; make

test:
	cd test; make
