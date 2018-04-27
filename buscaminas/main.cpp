#include <iostream>
#include <ncurses.h>
#include "tablero.h"

#define N_MOVES 2
#define Y_GAME 5
#define SEPARA_GAME 2

#define COLUMNAS 3
#define FILAS 3

#define CHAR_BLOCK "██"
#define CHAR_BOMB "💣"


Tablero *tbombas;
Tablero *tvista;

int x=0, y=Y_GAME, p =0;

int fila =0, columna=0;

int checkcords(int y, int x) {
    if(x < 0 || y < Y_GAME || x > (FILAS-1)*SEPARA_GAME  || y > ((COLUMNAS-1) ) + Y_GAME )
        return 0;
    return 1;
}

void changecords(int ny, int nx) {
    if(checkcords(ny,nx)) {
        x = nx;
        y = ny;
    }

}
void init() {
    tbombas = new Tablero(FILAS);
    (*tbombas).setCelda(0,1, 1);
    tvista = new Tablero(FILAS);
}
void moveCursor(int y, int x) {
    attron(COLOR_PAIR(2));
    move(y, x);
    mvprintw(y,x,CHAR_BLOCK);
    attroff(COLOR_PAIR(2));
}
void ver(){
    attron(COLOR_PAIR(1));

    Tablero tablero = *tbombas;
    for (int f=0; f < tablero.getFilas(); f++){
        for (int c=0; c < tablero.getColumnas(); c++) {

            char* character = CHAR_BLOCK;

            if ((*tvista).getCelda(f,c) == 1)
            {
                int value = tablero.getCelda(f,c);

                if (value)
                    character = CHAR_BOMB;
                else
                    character = "  ";

            }
            mvprintw((f) + Y_GAME, c * SEPARA_GAME,"%s", character);
        }
    }
    //attroff(COLOR_PAIR(1));
}

int main() {

    setlocale(LC_ALL,"");
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    curs_set(0);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);

    init();

    ver();

    moveCursor(y, x);

    while (true) {
        int ch = getch();
        switch(ch) {
            case KEY_UP:
                changecords(y -1, x);
                break;
            case KEY_DOWN:
                changecords(y +1, x);
                break;
            case KEY_LEFT:
                changecords(y, x - N_MOVES);
                break;
            case KEY_RIGHT:
                changecords(y, x + N_MOVES);
                break;
            case 10:
                int fila = (y- Y_GAME);
                int columna = x/SEPARA_GAME;
                tvista->setCelda(fila, columna, 1);
                break;
        }
        ver();

        moveCursor(y, x);
        refresh();

    }
    endwin();

    return 0;
}
