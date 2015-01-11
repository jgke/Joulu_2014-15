include config.mk

.PHONY: doc lib putkijuoksu test

all: lib putkijuoksu test

clean:
	cd doc; ${MAKE} clean
	cd lib; ${MAKE} clean
	cd src; ${MAKE} clean
	cd test; ${MAKE} clean
	cd test/performance; ${MAKE} clean

doc: lib
	cd doc; ${MAKE}
	cd test; ${MAKE} coverage

lib:
	cd lib; ${MAKE}

putkijuoksu: lib
	cd src; ${MAKE}

test: lib
	cd test; ${MAKE}

performance: lib
	cd test; ${MAKE} performance
