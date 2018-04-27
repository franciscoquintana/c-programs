//
// Created by fquintana on 12/04/18.
//

#ifndef BUSCAMINAS_TABLERO_H
#define BUSCAMINAS_TABLERO_H


class Tablero {
private:
    int filas;
    int columnas;
public:
    Tablero(int size);
    int getCelda(int fila, int celda);
    int** array;

    void CreateArray(int size);

    int getFilas() const;

    int getColumnas() const;

    void setCelda(int fila, int celda);

    void setCelda(int fila, int celda, int value);

    void zero();
};


#endif //BUSCAMINAS_TABLERO_H
