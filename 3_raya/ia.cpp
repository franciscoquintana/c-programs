#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "3raya.h"
#include "ia.h"

#define M 3
#define N 3
#define J1 1
int probabilidad(int fila, int columna, int J) {
    //pos vertical, horizontal, diagonal1, diagonal2;
    int posibilidades[4] = {0,0,0,0};
    for(int f=0; f<M; f++)
        for(int c=0; c<N; c++) {
            if(tablero[f][c] == J && !(f == fila && c == columna)) {
                if(c == columna)
                    posibilidades[0]++;
                else if(f == fila)
                    posibilidades[1]++;
                else if((c - columna == f - fila) || columna - c  == fila - f)
                    posibilidades[2]++;
                else if(c - columna == fila - f || columna - c == f - fila)
                    posibilidades[3]++;
            }
            if(tablero[f][c] == 2) {
                if((f+1 == fila || f-1 == fila) && c == columna) {
                    if(tablero[f+1][c] == 1 || tablero[f-1][c] == 1)
                        posibilidades[0]--;
                }else if((c+1 == columna || c-1 == columna) && f == fila) {
                    if(tablero[f][c+1] == 1 || tablero[f][c-1] == 1)
                        posibilidades[1]--;
                } else if(c-1 == columna && f-1 == fila) {
                    if(tablero[f-1][c-1] == 1)
                        posibilidades[2]--;
                } else if(c+1 == columna && f+1 == fila) {
                    if(tablero[f+1][c+1] == 1)
                        posibilidades[2]--;
                } else if(c-1 == columna && f+1 == fila) {
                    if(tablero[f+1][c-1] == 1)
                        posibilidades[3]--;
                } else if(c+1 == columna && f-1 == fila) {
                    if(tablero[f-1][c+1] == 1)
                        posibilidades[3]--;
                }
            }
        }
    int mvalue = 0;
    for(int i=0; i<4; i++)
        if(posibilidades[i] > mvalue)
            mvalue = posibilidades[i];
    return mvalue;
}

int randr(unsigned int min, unsigned int max)
{
    double scaled = (double)rand()/RAND_MAX;
    return (max - min +1)*scaled + min;
}

void calc(int *y, int *x)
{
    int localy, localx;
    int mvalue = 0;
    int **values = NULL;
    int amount = 0;

    srand(time(NULL));

    for(int f=0; f<M; f++)
        for(int c=0; c<N; c++) {
            if(tablero[f][c] == 0) {
                if(probabilidad(f,c,1) == 2) {
                    if(mvalue < 2) {
                        localx = c;
                        localy = f;
                        mvalue = 2;
                        amount = 0;
                    }
                }  else {
                    int value = probabilidad(f,c,2);
                    if(value == 2)
                        int a;
                    if(value > mvalue)
                        amount = 0;
                    if(value >= mvalue) {
                        values = (int **) realloc(values, (amount + 1 ) * sizeof(int *));
                        *(values + amount) = (int *) malloc(2 * sizeof(int));
                        int *local = *(values + amount++);
                        *(local) = f;
                        *(local + 1) = c;
                        mvalue = value;
                    }
                }
            }
        }
    if(amount != 0) {
        int rand = randr(0, amount-1);
        int *local = *(values + rand);
        *y = *local;
        *x = *(local + 1);
    }
    else {
        *y = localy;
        *x = localx;
    }



}
