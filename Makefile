SRCDIR=src
BINDIR=bin
OBJDIR=obj
LIBDIR=lib

LIBSPRE=libncurses.a libtinfo.a libgpm.a
LIBSLINKER=$(LIBSPRE:%=$(LIBDIR)/%)
SOURCES=main.c ui.c
OBJECTSPRE=$(SOURCES:%.c=%.o)
OBJECTSLINKER=$(OBJECTSPRE:%=$(OBJDIR)/%)
EXECUTABLE=ziege


CC=gcc
CFLAGS=-c -Wall -std=c99 -I$(SRCDIR)
LDFLAGS=-static

all: ziege

ziege: main.o ui.o
	mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJECTSLINKER) -o $(BINDIR)/$@ $(LIBSLINKER)

%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@

.PHONY=clean

clean:
	rm -rf $(BINDIR)/*
	rm -rf $(OBJDIR)/*
