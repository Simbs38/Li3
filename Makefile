CFLAGS= -ansi -O2
OBJS=$(wildcard *.h *.c)

compile:$(OBJS)
		$(CC) $(CFLAGS) -o gereVendas $(OBJS) 

doc:$(OBJS)
		doxygen

clean:
	rm gereVendas

pdf:
	pdflatex relatorio.tex
