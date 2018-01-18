#include <stdio.h>
#include <stdlib.h>

int main(){
    char bit1, bit2;
    int salida = 0;

    printf("El bit 1 vale 0 o 1:\n");
    scanf(" %[0-1]", &bit1);

    printf("El bit 2 vale 0 o 1:\n");
    scanf(" %[0-1]", &bit2);

    if (bit2 == '1')
        salida = 2;

    if (bit1 == '1')
        salida++;

    printf("El numero es %i\n", salida);

    return EXIT_SUCCESS;
}
