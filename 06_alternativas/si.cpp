#include <stdio.h>
#include <stdlib.h>

int main(){
    int numero;

    printf("Numero: ");
    scanf(" %i", &numero);

    if (numero % 2 == 0) {
        printf("El numero %i es par.\n", numero);
        printf("Y los pares me gustan");
    } else
        printf("Impar de mierda!\n");
    printf("Y Colorín colorad ese cuento se ha  \n");
    return EXIT_SUCCESS;
}
