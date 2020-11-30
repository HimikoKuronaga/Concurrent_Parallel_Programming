DESTDIR=/usr/local/bin
PROYECTO=
CC=gcc
CFLAGS=-Wall
LFLAGS=-lm
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

all:$(PROYECTO)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

.PHONY:clean install uninstall
