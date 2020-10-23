PROYECTO=proc3
CFLAGS=-Wall
LFLAGS=-lm
CC=gcc
OBJECTS=$(patsubst %.o,%.c, $(wildcard *.c))

all:$(PROYECTO)

%.o:%.c
	$(CC) -c $< $(CLFAGS)

$(PROYECTO):$(OBJECTS)
	$(CC) -o $@ $<

.PHONY: clean

clean:
	rm *.o
