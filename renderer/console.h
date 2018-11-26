#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <termios.h>
#include "map.h"

#define KEY_CTRL 0x1d
#define KEY_C 0x2e

#define KEY_A 0x1e
#define KEY_W 0x11
#define KEY_S 0x1f
#define KEY_D 0x20

#ifdef __cplusplus
extern "C" {
#endif
    extern IntMap mapKeys;
    void showCursor(bool show);
    void reset_input_mode ();
    void set_input_mode ();
    int kbhit();
    void* readKeyboard(void* param);
#ifdef __cplusplus
}
#endif

#endif

