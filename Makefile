SRCDIR=src
BINDIR=bin
OBJDIR=obj
LIBDIR=lib

LIBSPRE=libncurses.a libtinfo.a libgpm.a
LIBSLINKER=$(LIBSPRE:%=$(LIBDIR)/%)
DYNLIB=ncurses
SOURCES:=$(shell cd $(SRCDIR) && ls *.c)
OBJECTSPRE=$(SOURCES:%.c=%.o)
OBJECTSLINKER=$(OBJECTSPRE:%=$(OBJDIR)/%)
EXECUTABLE=ziege

CC=gcc
CFLAGS=-c -std=c99 -I$(SRCDIR)
LDFLAGS=

all: ziege

ziege: $(OBJECTSPRE)
	mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJECTSLINKER) -o $(BINDIR)/$@ -l$(DYNLIB)

%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@

.PHONY=clean

clean:
	rm -rf $(BINDIR)/*
	rm -rf $(OBJDIR)/*
