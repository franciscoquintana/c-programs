CC = g++
CFLAGS = -g
.PHONY: clean

all: build

build: common.o uuid_map.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o
