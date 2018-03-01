#include <stdio.h>
#include <stdlib.h>

#define N 26

bool isvocal(char letra){
   return letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u';
}
int main(){
    char letra;

    char frase[] = "Mi moto alpina derrapante.";
    char* moto = frase;

do {
printf("Introduza la vocal por la que quiere sustituir en la frase: ");
scanf(" %s", &letra);
} while(!isvocal(letra));

  printf(" %s\n", frase);
  for(int i= 0; i < N; i++) {
      char *temp = (moto+i);
      if(isvocal(*temp))
	*temp = letra;
  }
  printf(" %s\n", frase);



return EXIT_SUCCESS;
}
