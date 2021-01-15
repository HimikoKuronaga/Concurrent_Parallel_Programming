# Archivo makefile simple
PROYECTO=procesos2
DESTDIR=/usr/local/bin
CFLAGS= -Wall
LFLAGS=-lm
CC=gcc

OBJECTS=$(patsubst %.c,%.o, $(wildcard *.c))
# Por cada archivo con extension .c, en la variable 'OBJECTS' se colocara 
# ese archivo pero con la extension .o

# $(wildcard pattern) <- Estructura general
# Esta expresion es reemplazada por cualquier archivo (o lista de archivos)
# cuyo nombre hace match con el patron que se pasa como parametro.

# $(patsubst %a, %b, var) <- Estructura general
# Esta funcion toma a la variable 'var' y reemplaza toda 'a' en esta variable
# con 'b'. 'a' puede ser un patron, al igual que 'b',
# 'var' puede ser una lista de archivos.


# Variables automaticas: '$@' <- Objetivo de la regla
# Variables automaticas: '$<' <- primera dependencia de una regla
# Variables automaticas: '$^' <- Lista de todas las dependencias de la regla

%.o:%.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LFLAGS)

.PHONY:clean

install:
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR) ; \
	fi; \

	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

clean:
	rm $(PROYECTO) *.o *.dat
