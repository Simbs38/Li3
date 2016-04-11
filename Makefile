OBJS=$(wildcard src/*.c)

CFLAGS= -ansi -O2 

compile:$(OBJS)
		$(CC) $(CFLAGS) -o gereVendas $(OBJS) 

run:
	./gereVendas

doc:$(OBJS)
		doxygen doxygen.conf

clean:
	rm gereVendas

pdf:
	pdflatex relatorio.tex
