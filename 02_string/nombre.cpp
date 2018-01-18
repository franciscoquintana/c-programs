
#include <stdio.h>
#include <stdlib.h>


int main(){
    char nombre[256];
    printf("Dime tu nombre\n");
    scanf(" %s", &nombre[0]);
    printf("Hola, %s.\n", nombre);
    return EXIT_SUCCESS;
}
