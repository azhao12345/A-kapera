CC = gcc
CFLAGS = -g -O3 -Wall -std=c11
SRCDIR = src
BINDIR = bin

all: akapera

akapera: $(SRCDIR)/akapera.c
	$(CC) $(CFLAGS) $(SRCDIR)/akapera.c -o $(BINDIR)/akapera

test: akapera
	$(BINDIR)/akapera

clean:
	rm $(BINDIR)/akapera
