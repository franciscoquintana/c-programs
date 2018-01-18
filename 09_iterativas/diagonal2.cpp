#include <stdio.h>
#include <stdlib.h>

#define A 5
int main(){
    for (int i = 0; i<A; i++) {
        for (int d=0; d<A; d++)
        {
            if (A-1-i == d)
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
