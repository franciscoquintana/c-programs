#include "common.h"

void enviaStr(int server_fd, char *str) {
    int len = strlen(str);
    write(server_fd, &len, sizeof(int));
    write(server_fd, str, len * sizeof(char));
}

//Hacer luego un free
char* leeStr(int server_fd) {
    int len;
    read(server_fd, &len, sizeof(int));
    int size = len * sizeof(char);
    char *str = (char *) malloc(size + 1);
    read(server_fd, str, size);
    *(str + size) = '\0';
    return str;
}
