#include "common.h"

#define N 0X0F

char buffer[GRANDE];

void rellenaBuffer( char *nameFile ) {
    FILE *file = fopen(nameFile, "r");
    char *pBuffer = (char *) malloc (N * sizeof(char));
    while(fgets(pBuffer, N, file) != NULL) {
        strcat(buffer, pBuffer);
    }
    free(pBuffer);
    fclose(file);
}

void enviaBuffer(int server_fd) {
    enviaStr(server_fd, buffer);
}
    
int connect() {
    int sock_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t size = sizeof(addr);

    int error = connect(sock_fd, (struct sockaddr *) &addr, size);

    if(error != -1)
        return sock_fd;
    else {
        fprintf(stderr,"Error al conectar al servidor\n");
        exit(1);
    }
}

int main() {
  rellenaBuffer("palabras.txt");

  int server_fd = connect();

  enviaBuffer(server_fd);
  printf("Lista enviada\n");

  char * respuesta = leeStr(server_fd);
  printf("RESPUESTA: %s\n", respuesta);
  free(respuesta);

  close(server_fd);
}
