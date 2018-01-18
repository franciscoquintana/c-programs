#include <stdio.h>
#include <stdlib.h>

void leerOpcion(int *opcion, int max) {
    int opcionTemp;
    scanf(" %i", &opcionTemp);
    if( opcionTemp > max )
    {
        printf("Opción invalida\n");
        leerOpcion( opcion, max );
    }
    else
    {
      *opcion = opcionTemp;
    }

}

void menu(int *opcion) {
    printf("Opciones:\n");
    printf("1: Nuevo\n");
    printf("2: Editar\n");
    printf("3: Eliminar\n");
    leerOpcion( opcion, 3 );
}

int main(){
    int opcion;

    menu(&opcion);

    printf("Has elegido la opcion: %i\n", opcion);

    return EXIT_SUCCESS;
}
