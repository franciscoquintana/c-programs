#include <stdio.h>
#include <stdlib.h>

int LeerNumero(int min, int max)
{
    int numero;
    int sucess = 0;
    while (!sucess)
    {

      scanf(" %i", &numero);

      if (numero >= min && numero <= max)
        sucess = 1;
      else
        printf("Numero invalido, el numero tiene que estar entre %i y %i.\n",min, max);
    }
    return numero;
}

int main(){

    int rojo,azul,amarillo;

    printf("Indica con 0 o 1 si es rojo:\n");
    rojo = LeerNumero(0,1);
    printf("Indica con 0 o 1 si es azul:\n");
    azul = LeerNumero(0,1);
    printf("Indica con 0 o 1 si es amarillo:\n");
    amarillo = LeerNumero(0,1);

    printf("Tu color es el ");

    if (rojo)
        if (azul && amarillo)
            printf("Blanco");
        else if (amarillo)
            printf("Naranja");
        else if (azul)
            printf("Morado");
        else
            printf("Rojo");
    else if (azul)
      if (amarillo)
          printf("Verde");
      else
          printf("Azul");
    else if (amarillo)
      printf("Amarillo");
    else
      printf("Negro");


    printf("\n");


	return EXIT_SUCCESS;
}
