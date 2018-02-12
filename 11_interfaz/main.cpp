
#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

void ver(matriz matriz){
    for (int f=0; f<matriz.fila; f++){
        for (int c=0; c<matriz.columna; c++)
            printf("%6.2lf", matriz.m[f][c]);
        printf("\n");
    }
    printf("\n");
}

void preguntaMatriz(matriz *matriz) {
    char term[2];
    double dato;
    double **m;
    int index, subindex, lastsubindex;
    lastsubindex = -1;
    index = 0;
    bool error = false;


    do {
        printf("Introduzca una matriz: \n"
                       "Ejemplo: [(4,7,8)(2,7,8)(4,9,5)]\n\t<==>\n"
                       "\t4 7 8\n"
                       "\t2 7 8\n"
                       "\t4 9 5\n"
                       "\n\tMatriz: ");
        error = false;
        scanf(" %*1[[]");
        do {
            m = (double **) realloc(m, (index + 1) * sizeof(*m));
            subindex =0;
            scanf(" %*1[(]");
            do {
                scanf(" %lf %*1[,]", &dato);
                m[index] = (double *) realloc(m[index], (subindex + 1) * sizeof(double));
                m[index][subindex++] = dato;
            } while( scanf(" %1[)]", term) == 0 );
            if(lastsubindex == -1)
                lastsubindex = subindex;
            if (lastsubindex != subindex)
                error = true;
            scanf(" %*1[,]");
            index++;
        } while( scanf(" %1[]]", term) == 0 );
        if(error)
            printf("Las columnas no coinciden\n");
    } while(error);

    matriz->m = m;
    matriz->fila = index;
    matriz->columna = subindex;
}

int main(){

    matriz matriz1, matriz2, resultado;
    int comun;

    preguntaMatriz(&matriz1);
    ver(matriz1);
    preguntaMatriz(&matriz2);
    ver(matriz2);

    if(matriz1.columna == matriz2.fila)
        comun = matriz1.columna;
    else {
        printf("Error el tamaño de las matrices no coincide, el numero de filas de la matriz 1 y las columnas de la matriz 2 no es el mismo");
        return 1;
    }

    for (int i=0; i<matriz1.fila; i++)
        for(int j=0; j<matriz2.columna; j++) {
            resultado.m[i][j] = 0;
            for (int k=0; k<comun; k++)
                resultado.m[i][j] += matriz1.m[i][k] * matriz2.m[k][j];
        }

    resultado.columna = matriz2.columna;
    resultado.fila = matriz1.fila;
    ver(resultado);

    return EXIT_SUCCESS;
}