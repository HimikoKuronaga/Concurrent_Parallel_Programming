PROYECTO=proc4
CFLAGS= -Wall
LFLAGS= -lm
CC= gcc
OBJECTS= $(patsubst %o,%c, $(wildcard *.c))


all:$(PROYECTO)

%.o:%.c
	$(CC) -c $< $(CFLAGS)


$(PROYECTO):$(OBJECTS)
	$(CC) -o $@ $(OBJECTS) 

.PHONY: clean


clean:
	rm *.o

install:

uninstall:



