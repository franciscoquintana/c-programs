#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){

    double grados, velocidad, radianes;
    printf("Angulo: ");
    scanf("%lf", &grados);
    printf("Velocidad: ");
    scanf("%lf", &velocidad);

    radianes = (grados * M_PI) / 180;
    

    return EXIT_SUCCESS;
}
