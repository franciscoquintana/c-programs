#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Introduce el lado: ");
    scanf(" %i",&n);
    for (int f=0; f<n; f++) {
        for(int c=0; c<n-f; c++)
           printf("*");
        printf("\n");
    }
    return EXIT_SUCCESS;
}
