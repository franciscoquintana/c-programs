CC = g++
CFLAGS = -g

.PHONY: clean

all: ahorcado


ahorcado: interfaz.o ahorcado.o
	$(CC) $(CFLAGS) -o ahorcado ahorcado.o interfaz.o -l ncursesw

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o
