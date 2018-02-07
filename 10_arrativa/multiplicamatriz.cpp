
#include <stdlib.h>
#include <stdio.h>

#define max 100
int Af =3;
int Comun;
int Bc =2;

void ver(double a[max][max]){
    for (int f=0; f<Af; f++){
        for (int c=0; c<Comun; c++)
            printf("%6.2lf", a[f][c]);
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
}

int main(){
    double a[max][max], b[max][max], r[max][max];

    pregunta();

    printf("Matriz 1:\n");
    preguntaDatos(Af,Comun,a);
    printf("Matriz 2:\n");
    preguntaDatos(Comun,Bc,b);

    for (int i=0; i<Af; i++)
        for(int j=0; j<Comun; j++) {
            r[i][j] = 0;
            for (int k=0; k<Comun; k++)
              r[i][j] += a[i][k] * b[k][j];
        }
    ver(r);

	return EXIT_SUCCESS;
}
