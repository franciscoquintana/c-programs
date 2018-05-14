#include <stdio.h>
#include <stdlib.h>

#define MAX 0x100

typedef struct {
  double x;
  double y;
} Coor2d;

typedef struct {
    Coor2d pos;
    Coor2d vel;
    Coor2d acc;
    void (*haz)(Coor2d *pos, Coor2d *vel, Coor2d *acc);
} Objeto;

typedef struct {
    Objeto data[MAX];
    int cima;
} Pila;

bool push(Objeto dato, Pila *pila){
    if (pila->cima >= MAX){
        return false;
    }
    pila->data[pila->cima++] = dato;
    return true;
}

Objeto pop(Pila *pila) {
    if (pila->cima == 0){
        return Objeto();
    }
    return pila->data[--pila->cima];
}

void haz_a (Coor2d *pos, Coor2d *vel, Coor2d *acc) {
    (*pos).x += (*vel).x * (*acc).x;
}

void haz_b (Coor2d *pos, Coor2d *vel, Coor2d *acc) {
    (*pos).y += (*vel).y * (*acc).y;
}

int main(){
    Pila pila;
    pila.cima = 0;

    Objeto ob1 = {{0,0},{5,1},{9,90}, haz_a}, ob2 {{0,0},{2,4},{0.3,9},haz_b}, ob3 {{0,0},{3,0.5},{9,30}, haz_a};

    push(ob1, &pila);
    push(ob2, &pila);
    push(ob3, &pila);

    while(pila.cima != 0) {
        Objeto objeto = pop(&pila);
        objeto.haz(&objeto.pos, &objeto.vel, &objeto.acc);
        printf("x: %06.2f, y: %06.2f\n", objeto.pos.x, objeto.pos.y);
    }

    return EXIT_SUCCESS;
}
