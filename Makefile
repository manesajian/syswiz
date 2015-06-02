CC=gcc
CFLAGS=-Wall
test: test.o linkedlist.o

clean:
	rm -f test test.o linkedlist.o
