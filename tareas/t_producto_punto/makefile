DESTDIR=/usr/local/bin
PROYECTO=punto
CFLAGS=-Wall
LFLAGS=-pthread
OBJECTS=$(patsubst %.c,%.o, $(wildcard *.c))

all:$(PROYECTO)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO):$(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

.PHONY: clean install uninstall 

clean:
	rm *.o $(PROYECTO)

install:
	if [! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi;\
		sudo cp $(PROYECTO) $(DESTDIR)

uninstall: 
	sudo rm $(DESTDIR)/$(PROYECTO)
