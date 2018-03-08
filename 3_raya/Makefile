CC = g++
CFLAGS = -g

.PHONY: clean

all: 3raya


3raya: 3raya.o ia.o
	$(CC) $(CFLAGS) -o 3raya 3raya.o ia.o -l ncursesw

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o
