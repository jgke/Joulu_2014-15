include ../config.mk

TARGETS=maarittely.pdf testaus.pdf vk1.pdf vk2.pdf

.PHONY: latex doxygen

%.pdf : src/%.tex
	${TEX2PDF} -o $@ src/$*.tex

all: latex doxygen

latex: ${TARGETS}

doxygen:
	doxygen Doxyfile

clean:
	rm -rf *.pdf doxygen coverage
