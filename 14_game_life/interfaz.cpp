#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <locale.h>

#include "interfaz.h"
#include "global.h"

#define CAR_LLENO "▒"
#define CAR_VACIO "░"


void pintar(int matriz[M][N]) {
    for (int fila=0; fila<M; fila++) {
        for (int col=0; col<N; col++)
            mvprintw(fila, col,"%s", matriz[fila][col]? CAR_LLENO : CAR_VACIO);
    }
}

void dame_coord(int *x, int *y) {
    mvprintw(M+1,0,"Usa unas coordenadas invalidas para terminar");
    mvprintw(M+2,0,"Nuevo x,y: ");
    scanw(" %i, %i", x, y);
    --*x, --*y;
}

void poblacion_inicial(int matriz[M][N]) {
    int x, y;

    do{
        erase();
        pintar(matriz);
        dame_coord(&x, &y);
        if ( SON_VALIDAS(x,y) )
            matriz[x][y] = (matriz[x][y] + 1) % 2;

    } while ( SON_VALIDAS(x,y) );
}

void rellena(int matriz[M][N]){
    int iniciales;
    int x, y;

    system("clear");
    printf("Cuántos puntos iniciales quieres?: ");
    scanf(" %i", &iniciales);

    for (int n=0; n<iniciales; n++) {
        x = rand() % M;
        y = rand() % N;
        matriz[x][y] = 1;
    }
}

void initUI() {
    setlocale(LC_ALL,"");
    initscr();
}
