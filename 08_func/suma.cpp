#include <stdio.h>
#include <stdlib.h>

int suma(int primerNumero, int segundoNumero) {
    return primerNumero + segundoNumero;
}

void leernumero(int *numero)
{
    printf("Introduce un numero\n");
    scanf(" %i", numero);
}

int main(){
    int resultado, numero1, numero2;
    leernumero(&numero1);
    leernumero(&numero2);
    resultado = suma(numero1,numero2);
    printf("Resultado: %i\n", resultado);
    return EXIT_SUCCESS;
}
