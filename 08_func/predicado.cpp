#include <stdio.h>
#include <stdlib.h>

int es_par(int number) {
    return !(number % 2);
}

bool es_p(int number) {
    if(number % 2)
        return false;
    return true;
}

int main(){
    if(es_par(2))
        printf("Es par. \n");
    return EXIT_SUCCESS;
}
