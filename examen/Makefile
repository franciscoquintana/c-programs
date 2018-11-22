CC = g++
CFLAGS = -g

.PHONY: clean

all: client server


client: client.o common.o
	$(CC) $(CFLAGS) -o client client.o common.o

server: server.o common.o
	$(CC) $(CFLAGS) -o server server.o common.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o
