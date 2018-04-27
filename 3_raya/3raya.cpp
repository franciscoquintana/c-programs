#include <curses.h>
#include <locale.h>
#include <unistd.h>
#include <stdio_ext.h>
#include "3raya.h"
#include "ia.h"
#include "interfaz.h"
#include "tablero.h"

#define N_MOVES 4
#define Y_GAME 5
#define SEPARA_GAME 4

#define CHAR_X "🗙"
#define CHAR_O "○"
#define CHAR_B "█"


bool IA = false;

enum Jugador {J1, J2};

Jugador jugador = J1;

int tablero[M][N];

int x=0, y=Y_GAME, p =0;

int fila =0, columna=0;

int checkcords(int y, int x) {
    if(x < 0 || y < Y_GAME || x > (N-1)*SEPARA_GAME  || y > ((M-1)*SEPARA_GAME ) + Y_GAME )
        return 0;
    return 1;
}

void changecords(int ny, int nx) {
    if(checkcords(ny,nx)) {
        x = nx;
        y = ny;
    }

}


void header(){
    mvprintw(0,0,"░▀▀█░░░█▀▀░█▀█░░░█▀▄░█▀█░█░█░█▀█");
    mvprintw(1,0,"░░▀▄░░░█▀▀░█░█░░░█▀▄░█▀█░░█░░█▀█");
    mvprintw(2,0,"░▀▀░░░░▀▀▀░▀░▀░░░▀░▀░▀░▀░░▀░░▀░▀");
}

void ver(int a[M][N]){
    for (int f=0; f<M; f++){
        for (int c=0; c<N; c++) {
            int value = a[f][c];
            char* character = CHAR_B;
            if(value == 2)
                character = CHAR_O;
            else if (value == 1)
                character = CHAR_X;
            mvprintw((f * SEPARA_GAME) + Y_GAME, c * SEPARA_GAME,"%s", character);
        }
    }
}

void rellena(int a[M][N]) {
    for (int f=0; f<M; f++){
        for (int c=0; c<N; c++)
            a[f][c] = 0;
    }
}
int updateGAME(bool *finish) {
    if(!checkFin())
        return 0;
    int winner = Winner();
    if(winner == -1) {
            erase();
            header();
            mvprintw(10,2,"NO HA GANADO NINGUN JUGADOR");
            refresh();
            sleep(2);
            *finish = true;
    } else {
            erase();
            header();
            mvprintw(10,2,"HAS GANADO JUGADOR: %i", winner + 1);
            refresh();
            sleep(5);
            *finish = true;
    }
    return 1;
}
void cambiarJ(bool *finish) {
    if(updateGAME(finish))
        return;
    erase();
    header();
    ver(tablero);
    jugador = jugador ? J1 : J2;
    mvprintw(4,0,"Jugador: %i",jugador + 1);
    if(IA && jugador == J2) {
        calc(&fila, &columna);
        tablero[fila][columna] = 2;
        cambiarJ(finish);
    }

    y = Y_GAME;
}
void preguntaNJ() {
    int numero;
    do {
        __fpurge(stdin);
        printf("Numero de Jugadores 1 o 2:");
        scanf(" %i", &numero);
    } while( numero < 1 || numero > 2);
    if (numero == 1)
        IA = true;
}

int main(){

    setlocale(LC_ALL,"");
    bool finish = false;
    rellena(tablero);
    preguntaNJ();
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    header();
    ver(tablero);
    mvprintw(4,0,"Jugador: %i",jugador + 1);
    move(Y_GAME,0);
    while (!finish) {
        int ch = getch();
        switch(ch) {
            case KEY_UP:
                changecords(y - N_MOVES, x);
                break;
            case KEY_DOWN:
                changecords(y + N_MOVES, x);
                break;
            case KEY_LEFT:
                changecords(y, x - N_MOVES);
                break;
            case KEY_RIGHT:
                changecords(y, x + N_MOVES);
                break;
            case 10:
                int *celda = &tablero[(y- Y_GAME)/SEPARA_GAME][x/SEPARA_GAME];
                if(*celda == 0) {
                    *celda = (jugador + 1);
                    fila = (y- Y_GAME)/SEPARA_GAME;
                    columna = x/SEPARA_GAME;
                    cambiarJ(&finish);
                }
                break;
        }
        move(y, x);
        refresh();
    }
    endwin();

}

