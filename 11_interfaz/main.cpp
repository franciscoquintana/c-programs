
#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

void ver(matriz matriz){
    for (int f=0; f<matriz.filas; f++){
        printf("\t");
        for (int c=0; c<matriz.columnas; c++)
            printf("%8.2lf", matriz.m[f][c]);
        printf("\n");
    }
    printf("\n");
}

void inicializa(matriz *m,int filas, int columnas) {
    double **matriz = NULL;
    matriz = (double **) realloc(matriz, filas * sizeof(columnas * sizeof(double)));
    for (int i = 0; i < columnas; ++i) {
        matriz[i] = (double *) realloc(matriz[i], columnas * sizeof(double));
    }

    m->m = matriz;
    m->filas = filas;
    m->columnas = columnas;
}

void preguntaMatriz(matriz *matriz) {
    char term[2];
    double dato;
    double **m = new double*[1];
    int index, subindex, filas = 0, columnas = 0;
    index = 0;

    printf("Introduzca una matriz: \n\n"
                   "Ejemplo: [(4,7,8)(2,7,8)(4,9,5)]\n\t<==>\n"
                   "\t4 7 8\n"
                   "\t2 7 8\n"
                   "\t4 9 5\n"
                   "\nMatriz: ");

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

        if (subindex > columnas)
            columnas = subindex;

        scanf(" %*1[,]");
        index++;

        if (index > filas)
            filas = index;

    } while( scanf(" %1[]]", term) == 0 );

    matriz->m = m;
    matriz->filas = filas;
    matriz->columnas = columnas;
}

int main(){

    matriz matriz1, matriz2, resultado;
    int comun;

    preguntaMatriz(&matriz1);
    ver(matriz1);
    preguntaMatriz(&matriz2);
    ver(matriz2);

    if(matriz1.columnas == matriz2.filas)
        comun = matriz1.columnas;
    else {
        printf("Error el tamaño de las matrices no coincide, el numero de filas de la matriz 1 y las columnas de la matriz 2 no es el mismo\n");
        return 1;
    }

    printf("Resultado:\n");

    inicializa(&resultado,matriz1.filas, matriz2.columnas);

    for (int i=0; i<matriz1.filas; i++) {
        for(int j=0; j<matriz2.columnas; j++) {
            resultado.m[i][j] = 0;
            for (int k=0; k<comun; k++)
                resultado.m[i][j] += matriz1.m[i][k] * matriz2.m[k][j];
        }
    }

    resultado.columnas = matriz2.columnas;
    resultado.filas = matriz1.filas;
    ver(resultado);

    return EXIT_SUCCESS;
}
