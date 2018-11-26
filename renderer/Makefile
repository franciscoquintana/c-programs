CC = g++
CFLAGS = -g

.PHONY: clean

all: example


example: example.o sprite_render.o png.o console.o map.o
	$(CC) $(CFLAGS) -o example example.o sprite_render.o png.o console.o map.o -lpng -lpthread

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o
