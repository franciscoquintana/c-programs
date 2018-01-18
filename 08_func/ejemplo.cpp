#include <stdio.h>
#include <stdlib.h>

#define N 5
int main(){
    for (int i=0; i<N; i++) {
        for(int d=0; d<N; d++)
          printf("*");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
