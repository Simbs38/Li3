CFLAGS= -ansi -O2
OBJS=$(wildcard *.c *.h)

compile:$(OBJS)
		$(CC) $(CFLAGS) -o li3 $(OBJS) 

doc:$(OBJS)
		doxygen

clean:
	rm li3

pdf:
	pdflatex relatorio.tex