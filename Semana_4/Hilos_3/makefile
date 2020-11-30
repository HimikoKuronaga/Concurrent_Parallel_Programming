DESTDIR=/usr/local/bin
PROYECTO=hilos
CC=gcc
CFLAGS=-Wall
LFLAGS=-lm -pthread
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

all:$(PROYECTO)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO):$(OBJS)
	$(CC) -o $@ $< $(LFLAGS)

.PHONY:clean install uninstall

clean:
	rm *.o $(PROYECTO)

install: 


uninstall: 
