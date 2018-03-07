#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

#define N 80
#define Y_COORD 5
#define X_COORD 5
#define Y_VIDA 3 
#define X_VIDA 5
#define M_VIDAS 3
int vidas;
char *word = NULL;
char *tword = NULL;
char *wordahorcado = NULL;

void calcWordahorcado() {
    int len = strlen(word);
    wordahorcado = (char *) malloc(len * sizeof(char));
    for (int i = 0; i< len; i++)
        *(wordahorcado + i) = '_';
}

void printWord() {
    mvprintw(Y_COORD, X_COORD,"%s", wordahorcado);
    refresh();
}

void printLifes() {
    /*for(int i=0; i<vidas; i++)
       mvprintw(Y_VIDA, X_VIDA + i, "🖤");
    for(int i=vidas; i<M_VIDAS; i++)
      mvprintw(Y_VIDA, X_VIDA + i, "♡'");*/
    mvprintw(Y_VIDA, X_VIDA, "VIDAS:%i", vidas);
    refresh();
}

void updateUI() {
    printWord();
    printLifes();
}
int checkifexists(char ch) {
    char *foundStr = strchr(tword, ch);
    if( foundStr == NULL)
        return -1;
    return foundStr - word;
}

int randr(unsigned int min, unsigned int max)
{
    double scaled = (double)rand()/RAND_MAX;
    return (max - min +1)*scaled + min;
}

void loadWord() {
    char **words = NULL;
    int index = 0;
    FILE *file;
    char buffer[N];
    file = fopen("words.txt","rt");

    while(fgets(buffer, N, file) != NULL) {
        int len = strlen(buffer);
        words = (char **) realloc(words, (index + 1) * sizeof (*words));
        *(words + index) = (char *) malloc(len * sizeof(char));
        strncpy(*(words + index), buffer, len - 1);
        printf("%s\n", *(words + index));
        index++;
    }

    int rindex = randr(0, index - 1);
    int len = strlen(*(words + rindex));
    word = (char *) malloc(len * sizeof(char));
    strncpy(word, *(words + rindex), len);
    fclose(file);
    free(words);
}

int main(){
    vidas = M_VIDAS;
    srand(time(NULL));
    loadWord();
    calcWordahorcado();
    initscr();
    while (vidas != 0) {

    }
    updateUI();
    sleep(20);
    endwin();
    //printf("%i\n", checkifexists('c'));
    return EXIT_SUCCESS;
}
