#include <stdio.h>
#include <stdlib.h>

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
    int mvalue = 0;
    for(int i=0; i<4; i++)
        if(posibilidades[i] > mvalue)
            mvalue = posibilidades[i];
    return mvalue;
}

void calc(int *y, int *x)
{
    int mvalue = 0;
    for(int f=0; f<M; f++)
        for(int c=0; c<N; c++) {
            if(tablero[f][c] == 0) {
                if(probabilidad(f,c,1) == 2) {
                    if(mvalue < 2) {
                        *x = c;
                        *y = f;
                        mvalue = 2;
                    }
                }  else {
                    int value = probabilidad(f,c,2);
                    if(value >= mvalue) {
                        mvalue = value;
                        *x = c;
                        *y = f;
                    }
                }
            }
        }
}
