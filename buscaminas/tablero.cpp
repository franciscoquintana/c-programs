//
// Created by fquintana on 12/04/18.
//

#include <cstdlib>
#include <strings.h>
#include "tablero.h"

Tablero::Tablero(int size) {
    filas = size;
    columnas = size;
    CreateArray(size);
    zero();
}

void Tablero::CreateArray(int size) {
    array = (int **) realloc(array, sizeof(*array) * size);
    for (int i = 0; i < size; ++i) {
        *(array + i) = (int *) realloc(*(array + i), sizeof(int) * size);
    }
}

void Tablero::zero(){
    for (int i=0; i<filas; i++)
        for (int c=0; c<columnas; c++)
            setCelda(i, c, 0);
}

int Tablero::getCelda(int fila, int celda) {
    int *filaArray = *(array + fila);
    return *(filaArray + celda);
}

void Tablero::setCelda(int fila, int celda, int value) {
    int *filaArray = *(array + fila);
    *(filaArray + celda) = value;
}

int Tablero::getFilas() const {
    return filas;
}

int Tablero::getColumnas() const {
    return columnas;
}
