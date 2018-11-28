CC = g++
FLAGS = -g -I../common/
VPATH=../common/

.PHONY: clean

all: example

example: example.o sprite_render.o font_render.o png.o console.o map.o common.o uuid_map.o
	$(CC) $(CFLAGS) -o example $^ -lpng -lpthread -lz -luuid

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o
