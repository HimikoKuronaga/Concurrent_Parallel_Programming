DESTDIR=/usr/bin
PROYECTO=sobel
CC=gcc
CFLAGS= -Wall
LFLAGS= -lm -lpthread
OBJECTS= $(patsubst %.c,%.o, $(wildcard *.c))

%.o:%.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO):$(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LFLAGS) 

.PHONY:clean

install:
	if [! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi;
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)
zip:
	zip -r $(PROYECTO).zip ./
clean: 
	rm *.o $(PROYECTO) *F*.bmp $(PROYECTO).zip
