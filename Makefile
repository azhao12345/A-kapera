CC = gcc
CFLAGS = -g -O0 -Wall -std=c11
OBJECTS = akapera.o

all: akapera

akapera: $(OBJECTS)

test: akapera
	./akapera

clean:
	rm *.o akapera
