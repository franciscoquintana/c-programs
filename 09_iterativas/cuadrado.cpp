#include <stdio.h>
#include <stdlib.h>

#define A 5
int main(){
    for (int i = 0; i<A; i++) {
        for (int d=0; d<A; d++)
            printf("*");
        printf("\n");
    }
    return EXIT_SUCCESS;
}
