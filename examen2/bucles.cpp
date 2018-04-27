int opcion;

do {
  __fpurge(stdin);
  printf("Dime un numero del 1 al 5: ");
  scanf(" %i", &opcion);
} while (opcion < 1 || opcion > 5);

printf("Opcion: %i\n", opcion);
