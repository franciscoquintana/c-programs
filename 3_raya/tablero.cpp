#include <stdio.h>
#include <stdlib.h>

#include "3raya.h"
#include "tablero.h"

int **getValidMoves(int *pamount) {
    int **ValidMoves = NULL;
    int amount = 0;
    for(int f = 0; f < M; f++) {
        for(int c = 0; c < N; c++)
            if(tablero[f][c] == 0) {
                ValidMoves = (int **) realloc(ValidMoves, (amount + 1) * sizeof(int *));
                *(ValidMoves + amount) = (int *) malloc(2 * sizeof(int));
                int *temp = *(ValidMoves + amount++);

                *(temp) = f;
                *(temp + 1) = c;
            }
    }
    *pamount = amount;
    return ValidMoves;
}

int getValue(int *Coords) {
    return tablero[*Coords][*(Coords + 1)];
}
int allEquals(int lista[3][2]) {
    int value = getValue(lista[0]);
    for(int e = 0; e < 3; e++) {
        if(value != getValue(lista[e]))
            return 0;
    }
    return 1;
}
int Winner() {
    int WinCords[8][3][2] = {{{0,0},{0,1},{0,2}}, {{1,0},{1,1},{1,2}}, {{2,0},{2,1},{2,2}}, // Vertical
        {{0, 0}, {1, 0}, {2, 0}}, {{0, 1}, {1, 1}, {2, 1}}, {{0, 2}, {1, 2}, {2, 2}}, // Horizontal
        {{0, 0}, {1, 1}, {2, 2}}, {{0, 2}, {1, 1}, {2, 0}}}; // Diagonales

    for(int i=0; i<8; i++)
        if(getValue(WinCords[i][0]) != 0 && allEquals(WinCords[i]))
          return getValue(WinCords[i][0]) - 1;
    return -1;
}

int checkFin() {
    int amount;
    int **Moves = getValidMoves(&amount);
    int r = 0;
    if(Winner() != -1 || amount == 0)
        r = 1;

    free(Moves);
    return r;
}
