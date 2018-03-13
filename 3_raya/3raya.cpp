#include <curses.h>
#include <locale.h>
#include <unistd.h>
#include <stdio_ext.h>
#include "3raya.h"
#include "ia.h"
#include "interfaz.h"

#define N_MOVES 4
#define Y_GAME 5
#define SEPARA_GAME 4

#define CHAR_X "🗙"
#define CHAR_ "○"


bool IA = false;

enum Jugador {J1, J2};

enum STATE {FINISH, WIN, PLAYING};

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
        for (int c=0; c<N; c++)
            mvprintw((f * SEPARA_GAME) + Y_GAME, c * SEPARA_GAME,"%i", a[f][c]);
    }
}

void rellena(int a[M][N]) {
    for (int f=0; f<M; f++){
        for (int c=0; c<N; c++)
            a[f][c] = 0;
    }
}
int checkGAME() {
    int valcelda = jugador + 1;

    //pos vertical, horizontal, diagonal1, diagonal2;
    int posibilidades[4] = {0,0,0,0};
    for(int f=0; f<M; f++)
        for(int c=0; c<N; c++)
            if(tablero[f][c] == valcelda && !(f == fila && c == columna)) {
                if(c == columna)
                    posibilidades[0]++;
                else if(f == fila)
                    posibilidades[1]++;
                else if((c - columna == f - fila) || columna - c  == fila - f)
                    posibilidades[2]++;
                else if(c - columna == fila - f || columna - c == f - fila)
                    posibilidades[3]++;
            }

    for(int i=0; i<4; i++)
        if(posibilidades[i] == 2)
            return WIN;

    int cuenta0 = 0;

    for (int f=0; f<M; f++)
        for (int c=0; c<N; c++) {
            int value = tablero[f][c];
            if (value == 0)
                cuenta0++;
        }

    if(cuenta0 == 0)
        return FINISH;

    return PLAYING;
}
int updateGAME(bool *finish) {
    switch(checkGAME()) {
        case PLAYING:
            return 0;
            break;
        case FINISH:
            erase();
            header();
            mvprintw(10,2,"NO HA GANADO NINGUN JUGADOR");
            refresh();
            sleep(2);
            *finish = true;
            break;
        case WIN:
            erase();
            header();
            mvprintw(10,2,"HAS GANADO JUGADOR: %i", jugador + 1);
            refresh();
            sleep(5);
            *finish = true;
            break;
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

