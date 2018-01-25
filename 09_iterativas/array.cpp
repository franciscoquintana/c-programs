#include <stdio.h>
#include <stdlib.h>
#define N 20
int sumaArray(int Array[],int from, int to) {
    int numero = 0;
    for (int i = from; i<to;i++) {
      numero += Array[i];
    }
    return numero;
}
int main(){
    int start = 1;
    int Array [N];
    Array[0] = start;
    Array[1] = start;
    for (int i = 2; i<N; i++)
        Array[i] = sumaArray(Array,i-2,i);

    for (int i = 0; i<N; i++)
        printf("%i|",Array[i]);
    printf("\n");
    return EXIT_SUCCESS;
}
