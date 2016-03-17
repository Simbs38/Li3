CFLAGS= -ansi -O2
OBJS=$(wildcard *.c)

compile:$(OBJS)
		$(CC) $(CFLAGS) -o li3 $(OBJS) 

doc:$(OBJS)
		doxygen

clean:
	rm -r li3
	

pdf:
	pdflatex relatorio.tex