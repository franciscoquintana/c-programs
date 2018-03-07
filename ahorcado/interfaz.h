#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include <curses.h>
#include <locale.h>
#include "ahorcado.h"

#define Y_COORD 5
#define X_COORD 5
#define Y_VIDA 3
#define X_VIDA 5

#ifdef __cplusplus
extern "C" {
#endif

    void updateUI();
    void initUI();

#ifdef __cplusplus
}
#endif

#endif
