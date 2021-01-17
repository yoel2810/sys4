frequency.o: frequency.c frequency.h
		gcc -Wall -g -c frequency.c -o frequency.o

frequency: frequency.o
		gcc -Wall -g -o frequency frequency.o

.PHONY: clean all

all: frequency frequency.o

clean:
		rm -f *.o *.a *.so frequency
