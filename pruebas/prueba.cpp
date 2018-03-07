#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define N_MOVES 1

int x=0, y=0, p =0;
int checkcords(int y, int x) {
    if(x < 0 || y < 0 || x > COLS || y > LINES)
        return 0;
    return 1;
}

void changecords(int ny, int nx) {
    if(checkcords(ny,nx)) {
        x = nx;
        y = ny;
    }

}

int main(){
    initscr();
    //createHandler();
    //getmaxyx(stdscr, nlines, ncols);
    keypad(stdscr, TRUE);
    noecho();
    mvaddch( 5, 3, 'a');
    //wrefresh(win);
    int ch;
    for(;;) {
        bool close = false;
        ch = getch();
        switch(ch) {
            case KEY_UP:
                changecords(y - N_MOVES, x);
                break;
            case KEY_DOWN:
                changecords(y + N_MOVES, x);
                break;
            case KEY_LEFT:
                changecords(y, x - N_MOVES);
                break;
            case KEY_RIGHT:
                changecords(y, x + N_MOVES);
                break;
            case KEY_RESIZE:
                clear();
                mvprintw(0, 0, "COLS = %d, LINES = %d", COLS, LINES);
                border(0, 0, 0, 0, 0, 0, 0, 0);
                break;
            case 'q':
                close = true;
                mvprintw(0,0, "EXIT");
                break;
        }
        move(y, x);
        refresh();
        if(close)
            break;
    }
    sleep(1);

    endwin();
    return EXIT_SUCCESS;
}
