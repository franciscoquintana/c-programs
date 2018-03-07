#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "ahorcado.h"
#include "interfaz.h"

char *word = NULL;
char *tword = NULL;
char *wordahorcado = NULL;
char *letras = NULL;
int vidas = 0;
int acertadas = 0;

char letrasm[M_VIDAS];
int indexletrasm = 0;

void calcWordahorcado() {
    int len = strlen(word);
    wordahorcado = (char *) malloc(len * sizeof(char));
    *(wordahorcado + len) = '\0';
    for (int i = 0; i< len; i++)
        *(wordahorcado + i) = '_';
}

int checkifexists(char ch, char *word) {
    char *foundStr = strchr(word, ch);
    if( foundStr == NULL)
        return -1;
    return foundStr - word;
}

void replace(char ch, char *word, int* pos, int amount) {
    for (int i=0; i < amount; i++)
        *(word + *(pos + i)) = ch;
}

int searchreplace(char ch, char *word, int* dest) {
    int amount=0;
    int chf = 0;
    while(chf != -1) {
        chf = checkifexists(ch, word);
        if(chf == -1)
            return amount;
        dest = (int *) realloc(dest, (amount + 1) * sizeof(int));
        *(dest + amount++) = chf;
        replace('_', word, &chf, 1);
    }
    return amount;
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

    bzero(buffer, N);

    file = fopen("words.txt","rt");

    while(fgets(buffer, N, file) != NULL) {
        int len = strlen(buffer);
        words = (char **) realloc(words, (index + 1) * sizeof (*words));
        *(words + index) = (char *) malloc(len * sizeof(char));
        strncpy(*(words + index), buffer, len - 1);
        index++;
    }

    int rindex = randr(0, index - 1);
    int len = strlen(*(words + rindex));

    word = (char *) malloc(len * sizeof(char));
    strncpy(word, *(words + rindex), len);
    fclose(file);
    free(words);
}

void initVars() {
    int len = strlen(word);
    tword = (char *) malloc(len * sizeof(char));
    *(tword + len) = '\0';
    strncpy(tword, word, len);

    letras = (char *) malloc(len  * sizeof(char));
    bzero(letras, len);
}

int main(){
    vidas = M_VIDAS;
    bool win = false;
    srand(time(NULL));
    loadWord();
    initVars();
    calcWordahorcado();
    initUI();
    while (vidas != 0i && !win) {
        int ch = getch();
        if(isalpha(ch) && checkifexists(ch, letras) == -1) {
            int *chars = (int *) malloc(sizeof(int));
            int amount = searchreplace(ch, tword, chars);
            acertadas += amount;
            if( amount == 0) {
                vidas--;
                letrasm[indexletrasm++] = ch;
            } else {
                replace(ch, wordahorcado, chars, amount);
                *(letras + strlen(letras)) = ch;
                if(acertadas == (int) strlen(word))
                    win = true;
            }
            free(chars);
        }
        updateUI();
    }
    endwin();
    if(win)
        printf("Has ganado\n");
    else
        printf("Vuelve a intentarlo, la palabra era: %s\n", word);

    free(word);
    free(tword);
    free(wordahorcado);
    free(letras);
    return EXIT_SUCCESS;
}
