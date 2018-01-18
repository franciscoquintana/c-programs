
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#define N 0x16

int main(){
    char nombre[N];
    int lista[N];
    char pepe[N];
    char no_[N] = { 'p', 'e', 'p', 'e', '\0' };
    char nom[N] = "pepe";

    nom[3] = 'a';
    printf("Ocupa: %lu bytes.\n", sizeof(nombre));
    printf("Ocupa: %X bytes.\n",(int) sizeof(nombre));
    printf("Ocupa: %lu bytes.\n", sizeof(lista));
    printf("Ocupa: %lu celdas.\n", sizeof(lista) / sizeof(int));

    printf("%c", nombre[0]);
    printf("%c", nombre[1]);
    printf("%c", nombre[2]);
    printf("%c", nombre[3]);
    printf("%c", nombre[4]);
    printf("\n");

    bzero(lista,sizeof(lista));
    memset(lista + 1, 3, 3);

    printf("%X.", lista[0]);
    printf("%X.", lista[1]);
    printf("%X.", lista[2]);
    printf("%X.", lista[3]);
    printf("%X.", lista[4]);
    printf("%X.", lista[5]);
    printf("\n");

    printf("Dime tu nombre: ");
    fgets(nombre, N, stdin);
    sprintf(pepe,"Hola, %s\n", nombre);
    printf("%s\n", pepe);
    return EXIT_SUCCESS;

}
