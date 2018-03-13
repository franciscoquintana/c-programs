#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "3raya.h"
#include "ia.h"
#include "tablero.h"

#define M 3
#define N 3
#define J1 1
int randr(unsigned int min, unsigned int max)
{
    double scaled = (double)rand()/RAND_MAX;
    return (max - min +1)*scaled + min;
}
int evalue(int p, int Jugador) {
    int Opponent;
    if(p == 2)
        Opponent = 1;
    else
        Opponent = 2;

    if(checkFin()) {
        int winner = Winner();
        if(winner == Jugador - 1)
            return 1;
        else if(winner == -1)
            return 0;
        else
            return -1;
    }

    int *tree = NULL;
    int amount = 0;

    int Vamount;
    int **Vmoves = getValidMoves(&Vamount);

    for(int i = 0; i < Vamount; i++) {
        tree = (int *) realloc(tree, (amount + 1) * sizeof(int));
        *(tree + amount++) = evaluaMovimiento(*(Vmoves + i), Jugador, Opponent);
    }
    free(Vmoves);

    if (p == Jugador) {
        int min = 1;
        for(int i = 0; i < amount; i++) {
            int temp = *(tree + i);
            if (temp == -1) {
                free(tree);
                return temp;
            }
            if(temp < min)
                min = temp;
        }
        free(tree);
        return min;
    }
    else {
        int max = -1;
        for(int i = 0; i < amount; i++) {
            int temp = *(tree + i);
            if (temp == 1)  {
                free(tree);
                return temp;
            }
            if(temp > max)
                max = temp;
        }
        free(tree);
        return max;
    }

    return -1;
}

int evaluaMovimiento(int* coords, int jugador, int p) {
    int y = *coords;
    int x = *(coords + 1);
    //Haz Movimiento
    tablero[y][x] = p;
    int r = evalue(p, jugador);
    //DesHaz
    tablero[y][x] = 0;
    return r;
}

void calc(int *y, int *x) {
    int Vcantidad;
    int **VMoves = getValidMoves(&Vcantidad);

    int **Moves = NULL;
    int amount = 0;
    int max = -1;
    for(int i = 0; i < Vcantidad; i++) {
        int *tempmove = *(VMoves + i);
        int y = *tempmove;
        int x = *(tempmove + 1);
        int value = evaluaMovimiento(tempmove, 2, 2);

        if (value > max) {
            max = value;
            amount = 0;
        }
        if(value == max) {
            Moves = (int **) realloc(Moves, (amount + 1) * sizeof(int *));
            *(Moves + amount) = (int *) malloc( 2 * sizeof(int));
            int *temp = *(Moves + amount++);
            *temp = y;
            *(temp + 1) = x;
        }
    }

    int rand = randr(0, amount-1);
    int *local = *(Moves + rand);
    *y = *local;
    *x = *(local + 1);
}
