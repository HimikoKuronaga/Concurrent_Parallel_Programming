DESTDIR=/usr/local/bin
PROYECTO=thilos
CC=gcc
CFLAGS=-Wall
LFLAGS=-lm -pthread
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

all:$(PROYECTO)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO):$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LFLAGS)

.PHONY:clean install uninstall

clean:
	rm *.o $(PROYECTO) *.zip

install:
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	sudo rm $(DESTDIR)/$(PROYECTO)

zip:
	zip -r hilos.zip ./
