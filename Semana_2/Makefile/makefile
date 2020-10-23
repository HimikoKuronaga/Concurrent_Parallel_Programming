# Archivo makefile simple

PROYECTO=muestreo
DESTDIR=/usr/local/bin
CFLAGS= -Wall
LFLAGS=-lm
CC=gcc

#$@ nombre del objetivo de una regla Objetivo:Dependencia

#Variables automaticas : '$<' <- primera dependencia de una regla

%.o:%.c
	$(CC) -c $< $(CFLAGS)

# Lista de todas las dependencias de la regla $^
$(PROYECTO):muestreo.o procesamiento.o archivos.o
	$(CC) $^ -o $@ $(LFLAGS)

.PHONY:clean

install:
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR) ; \
	fi; \

	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm *.o *.dat
