#include <stdio.h>
#include <stdlib.h>
#define T 4
int main(){
    int n;
    printf("Introduce el numero de cuadrados: ");
    scanf(" %i",&n);
    for (int f=0; f<T; f++) {
        for(int cua=0; cua <n; cua++)
	    for(int c=cua?1:0; c<T; c++)
            {
                if(c==f)
                    printf("*");
                else
                    printf(" ");
            }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
