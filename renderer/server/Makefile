CC = g++
FLAGS = -g -I../common/
VPATH=../common/

all: server

server: server.o common.o uuid_map.o
	$(CC) $(CFLAGS) -o server $^ -lpthread -luuid

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<


.PHONY: clean
clean:
	$(RM) *.o
