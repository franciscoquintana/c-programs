#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    initscr();
    int x=0, y=0;
    WINDOW *win = newwin(20,30,x,y);
    keypad(stdscr, TRUE);

    int ch;
    for(;;) {
        ch = getch();
        switch(ch) {
            case KEY_UP:
                wmove(win,++y,x);
                break;
            case KEY_DOWN:
                wmove(win,--y,x);
                break;
        }
        wrefresh(win);
    }

    wmove(win, 5,5);
    wrefresh(win);
    sleep(20000);
    endwin();
    return EXIT_SUCCESS;
}
