#include "console.h"
#include "example.h"

#define KEY_UP 0x80

int key_ctrl = 0, key_c = 0;

IntMap mapKeys;

struct termios saved_attributes;
int saved_mode;

void showCursor(bool show) {
#define CSI "\e["
    if (show) {
        fputs(CSI "?25h", stdout);
    }
    else {
        fputs(CSI "?25l", stdout);
    }
#undef CSI
}

void reset_input_mode ()
{
    tcsetattr (0, TCSAFLUSH, &saved_attributes);
    ioctl(0, KDSKBMODE, saved_mode);
    showCursor(true);
}

void set_input_mode ()
{
    struct termios tattr;
    /* Make sure stdin is a terminal. */
    if (!isatty (STDIN_FILENO))
    {
        exit (EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr (STDIN_FILENO, &saved_attributes);

    /* Set the funny terminal modes. */
    tcgetattr (STDIN_FILENO, &tattr);

    tattr.c_lflag &= ~(ICANON | ECHO | ISIG);
    tattr.c_iflag &= ~(ISTRIP | INLCR | ICRNL | IGNCR | IXON | IXOFF);
    tattr.c_cc[VMIN] = 1;

    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);

    showCursor(false);

    ioctl(0, KDGKBMODE, &saved_mode);
    ioctl(0, KDSKBMODE, K_RAW);
}


int kbhit()
{
    struct timeval tv = { 0L, 0L  };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}


char readKey() {
    char c;
    //read (STDIN_FILENO, &c, 1);

    read (STDIN_FILENO, &c, 1);
    //ESCAPE
    if (c == 27) {
        read (STDIN_FILENO, &c, 1);
        read (STDIN_FILENO, &c, 1);

        c = readKey();
    }

    return c;
}

void* readKeyboard(void* param)
{
    int keyCode = 0;
    int res;

    init_map(&mapKeys);

    /* read scan code from stdin */
    res = read(0, &keyCode, 1);
    /* keep reading til there's no more*/
    while (res >= 0 && !finish_program) {
        //printf("%x\n", keyCode);

        if(keyCode < KEY_UP)
            insert_map(&mapKeys, keyCode, 1);
        else
            insert_map(&mapKeys, keyCode - KEY_UP, 0);
        keyCode = 0;
        res = read(0, &keyCode, 1);
    }
    return NULL;
}
