CC=gcc
CFLAGS=-Wall -Wextra -pedantic

main: bitvector tests
	$(CC) $(CFLAGS) -o a.out bitvector.o tests.o

bitvector: bitvector.c bitvector.h
	$(CC) $(CFLAGS) -c bitvector.c

tests:
	$(CC) $(CFLAGS) -c tests.c

clean:
	rm -f *.o *.out *.h.gch
