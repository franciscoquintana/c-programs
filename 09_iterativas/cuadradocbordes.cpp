#include <stdio.h>
#include <stdlib.h>

#define A 5
int main(){
    for (int i = 0; i<A; i++) {
        for (int d=0; d<A; d++)
        {
            if (i == 0 || d == 0 || i == A-1 || d == A-1)
            {
                printf("*");
                continue;
            }
            printf(" ");
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
