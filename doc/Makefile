include ../config.mk

TARGETS=maarittely.pdf vk1.pdf

%.pdf : src/%.tex
	${TEX2PDF} -o $@ src/$*.tex

all: ${TARGETS}

clean:
	rm -f *.pdf
