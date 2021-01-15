PROYECTO=procesos2
CC=gcc
CFLAGS= -Wall
LFAGS= -Lm
OBJECTS= $(patsubst %.c,%.o, $(wildcard %.c))

all:$(PROYECTO)


%.o:%.c
	$(CC) $^
