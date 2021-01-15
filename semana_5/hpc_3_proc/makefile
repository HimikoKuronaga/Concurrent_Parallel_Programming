DESTDIR=/usr/local/bin
PROYECTO=hpc
CC=gcc
CFLAGS=-Wall
LFLAGS=-lm
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

all:$(PROYECTO)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO):$(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

.PHONY:clean install uninstall
