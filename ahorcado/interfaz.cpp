#include "interfaz.h"

#define CAR_VIDA "🖤"
#define CAR_SVIDA "💛"

void printWord() {
    mvprintw(Y_COORD, X_COORD, "%s", wordahorcado);
}

void printLetras() {
    mvprintw(0, 0, "Letras Acertadas: %s", letras);
    mvprintw(1, 0, "Letras Falladas: %s", letrasm);
}

void printLifes() {
    for(int i=0; i<vidas; i++)
        mvprintw(Y_VIDA, X_VIDA + i, CAR_VIDA);
    for(int i=vidas; i<M_VIDAS; i++)
        mvprintw(Y_VIDA, X_VIDA + i, CAR_SVIDA);
    mvprintw(Y_VIDA - 1, X_VIDA, "VIDAS:%i", vidas);
}

void updateUI() {
    clear();
    refresh();
    printLetras();
    printWord();
    printLifes();
    move(0, 0);
    refresh();
}

void initUI() {
    setlocale(LC_ALL,"");
    initscr();
    noecho();
    updateUI();
}
