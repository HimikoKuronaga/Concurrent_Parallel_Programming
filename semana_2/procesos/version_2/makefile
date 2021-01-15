PROYECTO=proc2
DESTDIR=/usr/local/bin
CFLAGS = -Wall
LDFLAGS= -lm
CC=gcc
OBJECTS=$(patsubst %.c,%.c,$(wildcard *.c))

%.o:%.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO):$(OBJECTS)
	$(CC) -o $@ $(OBJECTS) 
	
.PHONY: clean

install:
	if [ ! -d $(DESTDIR) ] ; then \
		sudo mkdir $(DESTDIR) ; \
	fi; \

	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO) 

clean:
	rm *.o
	
