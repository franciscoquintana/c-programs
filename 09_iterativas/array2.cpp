#include <stdio.h>
#include <stdlib.h>
#define N 20
int sumaArray(int Array[],int from, int to) {
    int numero = 0;
    if (from <0)
        from = 0;
    for (int i = from; i<to;i++) {
        numero += Array[i];
     }
    return numero;
}
int main(){
    int Array [N];
    int C;
    Array[0] = 1;
    printf("Cuantas celdas quieres que se sumen:");
    scanf("%i",&C);
    for (int i = 1; i<N; i++)
        Array[i] = sumaArray(Array,i-C,i);

    for (int i = 0; i<N; i++)
        printf("%i|",Array[i]);
    printf("\n");
    return EXIT_SUCCESS;
}
