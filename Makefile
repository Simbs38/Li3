CC=gcc

OBJS=$(wildcard src/*.c)

OBJS2=$(wildcard src/array_dinamico.c src/avl.c src/catalogo.c src/clientes.c src/faturacao.c src/filiais.c src/heap.c src/interpretador.c src/leituras.c src/produtos.c src/queries.c src/venda.c  test/*.c)

CFLAGS= -Wno-unused-result -O2 -ansi

compile:$(OBJS)
		$(CC) $(CFLAGS) -o gereVendas $(OBJS) 

debug:$(OBJS)
		$(CC) $(CFLAGS) -g -o gereVendas $(OBJS) 

run:
	./gereVendas

clean:
	rm gereVendas

cleanAll: clean
	-@rm -rf doc

.PHONY: doc
doc:$(OBJS)
		doxygen doxygen.conf

test:$(OBJS2)
	$(CC) $(CFLAGS) -o testaVendas $(OBJS2)	
