TARGETS=maarittely.pdf
FLAGS= -c -b

.PHONY: Makefile all clean

%.pdf : src/%.tex
	texi2pdf $(FLAGS) -o $@ src/$*.tex

all: ${TARGETS}

clean:
	rm -f *.pdf
