#include <stdio.h>
#include <stdlib.h>

int main(){
    for (int i = 0; i<10; i++)
        for (int d=0; d<10; d++)
            printf("%i%i\n", i,d);
    return EXIT_SUCCESS;
}
