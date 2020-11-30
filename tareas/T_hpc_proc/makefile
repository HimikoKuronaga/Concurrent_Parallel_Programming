DESTDIR=/usr/local/bin
PROYECTO=tareahpc
CC=gcc
CFLAGS=-Wall
LFLAGS=-lm
OBJECTS=$(patsubst %.c,%.o, $(wildcard *.c))

all:$(PROYECTO)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO):$(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

.PHONY:clean install uninstall zip

clean:
	rm *.o $(PROYECTO) ventana.dat producto.dat

install:
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi;\
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)\$(PROYECTO)

zip:
	sudo zip -r hpc_proc.zip ./ 
