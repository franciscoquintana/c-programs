#include <stdio.h>
#include <stdlib.h>

int main(){

    int op1;
    int op2;

    printf("Introduce el operando 1:\n");
    scanf(" %i",&op1);

    printf("Introduce el operando 2:\n");
    scanf(" %i",&op2);

    printf("%i + %i = %i\n", op1, op2, op1 + op2);

    return EXIT_SUCCESS;
}
