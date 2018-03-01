#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 0x100
#define T 4
int main(){
    char **m = NULL;
    int index = 0;
    char buffer[N];
    do {
        m = (char **) realloc(m, (index + 1) * sizeof(*m));
        printf("Nombre: ");
        scanf(" %[^\n]", buffer);
        int len = strlen(buffer)+1;
        *(m + index) = (char *) realloc(*(m + index), len * sizeof(char));
        strncpy(*(m+index), buffer, len);
        index++;
    } while(index <T);

    for(int i=0; i<T; i++)
      printf("El nombre de la lista en la posicion %i es: %s\n",i , *(m+i));
    


    return EXIT_SUCCESS;
}
