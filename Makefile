CC=gcc

OBJS=$(wildcard src/*.c)

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
