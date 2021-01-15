DESTDIR=/usr/bin
PROYECTO=imagen
CC=gcc
CFLAGS=-Wall
LFLAGS=-lm
OBJECTS=$(patsubst %.c,%.o, $(wildcard *.c))

all:$(PROYECTO)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO):$(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

.PHONY:clean install uninstall

clean:
	rm *.o 

install:
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)
