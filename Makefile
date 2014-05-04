SRCDIR=src
BINDIR=bin
OBJDIR=obj

CC=gcc
CFLAGS=-c -Wall -pedantic -std=c99 -I$(SRCDIR)
LDFLAGS=

all: ziege

ziege: main.o
	mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJDIR)/$< -o $(BINDIR)/$@

%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@

.PHONY=clean

clean:
	rm -rf $(BINDIR)/*
	rm -rf $(OBJDIR)/*
