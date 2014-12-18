include ../config.mk

TARGETS=maarittely.pdf

%.pdf : src/%.tex
	${TEX2PDF} -o $@ src/$*.tex

all: ${TARGETS}

clean:
	rm -f *.pdf
