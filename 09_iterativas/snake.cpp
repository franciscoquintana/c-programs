#include <stdio.h>
#include <stdlib.h>

#define L 3

int main(){

    int triangulos;

    printf("Cuantos triangulos quieres? ");
    scanf( "%i",&triangulos);

    for (int f=0; f<L; f++){
        for (int t=0; t<triangulos; t++)
            for (int c=t?1:0; c<L; c++)
                if (t %2 == 0 )
                  if (f == c)
                      printf("*");
                  else
                      printf(" ");
                else
                    if (f+c == L)
                        printf("*");
                    else
                        printf(" ");
        printf("\n");
    }

    return EXIT_SUCCESS;
}
