
#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

#define max 100
int Af, Comun, Bc;

void ver(int A, int C,double m[max][max]){
    for (int f=0; f<A; f++){
        for (int c=0; c<C; c++)
            printf("%6.2lf", m[f][c]);
        printf("\n");
    }
    printf("\n");
}

void ver(matriz matriz){
    for (int f=0; f<matriz.fila; f++){
        for (int c=0; c<matriz.columna; c++)
            printf("%6.2lf", matriz.m[f][c]);
        printf("\n");
    }
    printf("\n");
}

void pregunta(){
    printf("Nº Columas matriz 1/ Nº Filas matriz 2: ");
    scanf(" %i",&Comun);
    printf("Nº filas matriz 1: ");
    scanf(" %i",&Af);
    printf("Nº Columnas matriz 2: ");
    scanf(" %i",&Bc);
    printf("\n");
}

void preguntaDatos(int F, int C,double a[max][max]) {
    for (int f=0; f<F; f++) {
        printf("Introduce la fila %i\n",f+1);
        for (int c=0; c<C; c++) {
            printf("Introduce la columna %i: ",c+1);
            scanf("%lf", &a[f][c]);
        }
        printf("\n");
    }
    ver(F,C,a);
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
    double a[max][max], b[max][max], r[max][max];

    matriz matriz1;
    
    preguntaMatriz(&matriz1);

    ver(matriz1);

    pregunta();

    printf("Matriz 1:\n");
    preguntaDatos(Af,Comun,a);

    printf("Matriz 2:\n");
    preguntaDatos(Comun,Bc,b);

    for (int i=0; i<Af; i++)
        for(int j=0; j<Bc; j++) {
            r[i][j] = 0;
            for (int k=0; k<Comun; k++)
                r[i][j] += a[i][k] * b[k][j];
        }
    ver(Af,Bc,r);

    return EXIT_SUCCESS;
}