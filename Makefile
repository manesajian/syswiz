CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-g
test: test.o hashtable.o linkedlist.o

clean:
	rm -f test test.o hashtable.o linkedlist.o
