
#include <stdio.h>
#include <stdlib.h>


bool is_dotted(int f, int c, int S)
{
    if ((f/S)%2 == 0 && (c/S)%2 == 0)
      return 1;
    else if ((f/S)%2 != 0 && (c/S)%2 != 0)
      return 1;

    return 0;
}
int main(){

    int cuadrados, S;

    printf("¿Cuantos cuadrados quieres? ");
    scanf(" %i", &cuadrados);
    printf("Tamaño: ");
    scanf(" %i", &S);

    int size = cuadrados * S;

    for (int f=0; f<size; f++) {
        for (int c=0; c<size; c++)
        {
            if (is_dotted(f,c,S))
                printf("*");
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
