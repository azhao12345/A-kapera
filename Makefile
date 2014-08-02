CC = gcc
CFLAGS = -g -O3 -Wall -std=c11
OBJECTS = akapera.o

all: akapera

akapera: $(OBJECTS)

test: akapera
	./akapera

clean:
	rm *.o akapera
