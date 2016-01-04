#
# MAKEFILE pour les reunions
#

MAIN=$(wildcard *.main.tex)
BASE=$(patsubst %.tex,%, $(MAIN))
BASESHORT=$(patsubst %.main,%, $(BASE))
DIR=$(shell basename $${PWD})
TMP=$(BASE)
FILES=$(wildcard *.tex *.bib *.sty Makefile *.fig *.jpg *.png)

# Commandes
PDFLATEX=pdflatex
PDFLATEX_OPTIONS= -shell-escape -halt-on-error
# -interaction=batchmode

.PHONY:all
	
all: $(MAIN)
	@echo "\n\ncreation des gnuplots!\n\n"
	#gnuplot *.gnuplot
	@echo "\n\nPremiere passe !\n\n"
	$(PDFLATEX) $<
	@echo "\n\nDeuxieme passe !\n\n"
	$(PDFLATEX) $<
	@echo "\n\nTroisieme passe !\n\n"
	$(PDFLATEX) $<
	@echo rename $(BASE).pdf to $(DIR).pdf
	mv "$(BASE).pdf" "$(BASESHORT).pdf" 
	
clean:
	@echo "Nettoyage !\n\n"
	rm -f *.log
	rm -f *.aux
	rm -f *.tmp
	rm -f *.out
	rm -f *.ac[nr] *.gl[gos] *.alg *.xdy *.ist
	rm -f *.fdb_latexmk
	rm -f *~

superclean: clean
	@echo "Nettoyage (y compris des PDF) !\n\n"
	rm -f *.pdf
	rm -f *.tgz

dist:all
	mkdir -p $(TMP)
	cp $(FILES) $(TMP)
	tar zcvf "$(TMP).tgz" $(TMP)
	rm -Rf $(TMP)
