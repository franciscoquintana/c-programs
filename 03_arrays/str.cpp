#include <stdio.h>
#include <stdlib.h>

#define N 0x100

int main(){

    const char *p ="The world is "; // constante tipo cadena
    /* Pequeña lección sobre punteros
    char const *p; // Puntero a una constante Forma coherente de decir que el char es const.
    char * const p; // Puntero constante (fijo)
    char const * const p; // puntero fijo a una constante.
*/
// Puntero: Es una variable que contiene una dirección de memoria.


    char frase[N] = "a vampire.\n"; //Inicialización
    char *d = frase;





    printf(" d ocupa %lu bytes.\n", sizeof(d));
    return EXIT_SUCCESS;
}
