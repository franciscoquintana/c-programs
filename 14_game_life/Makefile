CC = g++
CFLAGS = -g

.PHONY: clean

all: life


life: interfaz.o life.o
	$(CC) $(CFLAGS) -o life life.o interfaz.o -lncursesw

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o
