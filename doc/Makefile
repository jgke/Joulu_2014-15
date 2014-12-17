SOURCES=src/maarittely.tex
FLAGS= -c -b

%.pdf : %.tex
	texi2pdf $(FLAGS) -o $(@F) $<

all: ${SOURCES:.tex=.pdf}
