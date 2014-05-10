SRCDIR=src
BINDIR=bin
OBJDIR=obj
LIBDIR=lib

LIBS=$(LIBDIR)/libncurses.a $(LIBDIR)/libtinfo.a
SOURCES=main.c ui.c
OBJECTS=$(SOURCES:%.o=%.c)
EXECUTABLE=ziege


CC=gcc
CFLAGS=-c -Wall -pedantic -std=c99 -I$(SRCDIR)
LDFLAGS=-static

all: ziege

ziege: main.o ui.o
	mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJDIR)/main.o $(OBJDIR)/ui.o -o $(BINDIR)/$@ $(LIBS)

%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@

.PHONY=clean

clean:
	rm -rf $(BINDIR)/*
	rm -rf $(OBJDIR)/*
