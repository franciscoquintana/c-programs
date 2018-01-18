#include <stdlib.h>
#include <stdio.h>

int main(){
	int bit1, bit2, salida;

	printf("¿Cuanto vale bit1?\n");
	scanf(" %i", &bit1);
	
	if (bit1 !=0 && bit1 !=1) {
	    printf("Bit1 invalido\n");
	return 1;
	}

	printf("¿Cuanto vale bit2?\n");
	scanf("%i", &bit2);

	if (bit2 !=0 && bit2 !=1) {
	    printf("Bit2 invalido\n");
	return 1;
	}

	if (bit2 == 0)
	{
		if (bit1 == 1)
			salida = 1;
		else 
			salida = 0;
	}
	else
	{
		if (bit1 == 1)
			salida = 3;
		else
			salida = 2;	
	}


	printf("El valor en decimal es %i\n",salida);
	

	



	return EXIT_SUCCESS;
}


