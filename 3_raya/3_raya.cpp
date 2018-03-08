#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <locale.h>
#include <unistd.h>

#define N_MOVES 4
#define Y_GAME 5
#define SEPARA_GAME 4
#define M 3
#define N 3
enum Jugador {J1, J2};
enum STATE {FINISH, WIN, PLAYING};
Jugador jugador = J1;
int tablero[M][N];
int x=0, y=Y_GAME, p =0;
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

void cambiarJ() {
    erase();
    header();
    ver(tablero);
    jugador = jugador ? J1 : J2;
    mvprintw(4,0,"Jugador: %i",jugador + 1);
    y = Y_GAME;
}
int checkGAME() {
    int fila = (y- Y_GAME)/SEPARA_GAME;
    int columna = x/SEPARA_GAME;
    int valcelda = tablero[fila][columna];

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
int main(){

    setlocale(LC_ALL,"");
    bool finish = false;
    rellena(tablero);
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
                    switch(checkGAME()) {
                        case PLAYING:
                            cambiarJ();
                            break;
                        case FINISH:
                            erase();
                            header();
                            mvprintw(10,2,"NO HA GANADO NINGUN JUGADOR");
                            refresh();
                            sleep(2);
                            finish = true;
                            break;
                        case WIN:
                            erase();
                            header();
                            mvprintw(10,2,"HAS GANADO JUGADOR: %i", jugador + 1);
                            refresh();
                            sleep(5);
                            finish = true;
                            break;
                    }
                }
                break;
        }
        move(y, x);
        refresh();
    }
    endwin();

}

