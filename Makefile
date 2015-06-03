CC=gcc
CFLAGS=-Wall
test: test.o hashtable.o linkedlist.o

clean:
	rm -f test test.o hashtable.o linkedlist.o
