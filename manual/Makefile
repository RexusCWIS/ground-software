.PHONY: all, clean, mrproper, distclean

DOC_TITLE = CWIS_Ground_Software_User_Reference_Manual.pdf
LATEXMK = latexmk $(JOBNAME)
JOBNAME = -jobname=$(basename $(DOC_TITLE)) -pdf

SRC = gs-manual.tex

all:
	$(LATEXMK) $(SRC)

clean:
	$(LATEXMK) -c $(SRC)

mrproper distclean:
	$(LATEXMK) -CA $(SRC)

