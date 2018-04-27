#include <stdio.h>
#include <stdlib.h>
#define DEBUG(...) printf(__VA_ARGS__);
#define N 0x100
typedef struct {
    int datos[N];
    int cima;
} Pila;

void push(int dato, Pila *pila) {
    pila->datos[pila->cima++] = dato;
    DEBUG("-> %5i\n", dato);
}
int pop(Pila *pila) {
    --pila->cima;
    DEBUG("<- %5i\n", pila->datos[pila->cima])
    return pila->datos[pila->cima];
}
int main(){
    Pila *pila = NULL;
    pila = (Pila *) malloc(sizeof(Pila));

    push(8, pila);
    push(345, pila);

    pop(pila);
    pop(pila);
    return EXIT_SUCCESS;
}
