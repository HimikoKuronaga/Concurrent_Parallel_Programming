DESTDIR=/usr/local/bin
PROYECTO=autocorrelacion
CFLAGS=-Wall
LFLAGS=-lpthread -lm
CC=gcc
OBJECTS=$(patsubst %.c,%.o, $(wildcard *.c))

all:$(PROYECTO)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO):$(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)


.PHONY:clean install uninstall zipp

clean:
	rm *.o *.zip  $(PROYECTO) ventana.dat producto.dat resultado.dat

zipp:
	zip -r procesos.zip ./

install:
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTIR)\$(PROYECTO)
