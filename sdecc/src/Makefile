CC=gcc
CFLAGS= -g -Wall -Wstrict-prototypes
.PHONY:	cleanobj

all:	test

test:	test.o ecc.o
	$(CC) $(CFLAGS) -o test test.o ecc.o

test.o:	test.c ecc.h 
	$(CC) $(CFLAGS) -c test.c

ecc.o:	ecc.c ecc.h
	$(CC) $(CFLAGS) -c ecc.c

clean: 
	rm -f *.o core* *.gch test 

cleanobj:	
	rm *.o


