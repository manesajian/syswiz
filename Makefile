CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-g
all: test syswiz

test: test.o hashtable.o linkedlist.o insertionsort.o

syswiz: syswiz.o

clean:
	rm -f test syswiz test.o hashtable.o insertionsort.o linkedlist.o syswiz.o
