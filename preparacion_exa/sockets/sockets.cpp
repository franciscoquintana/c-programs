#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

void handle_client(int client_fd) {
    int count;
    read(client_fd, &count, sizeof(int));
    char * texto = (char *) malloc(count * sizeof(char));
    read(client_fd, texto, count * sizeof(char));
    printf("READ:%s\n", texto);
    close(client_fd);
}

int main(){
    int sock_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = INADDR_ANY;

    int error = bind(sock_fd,(struct sockaddr *) &addr, sizeof(addr));

    if(error != 0) {
        printf("Failed to bind\n");
        exit(1);
    }

    listen(sock_fd, 1);

    do {
        socklen_t size = sizeof(addr);

        int client_fd = accept(sock_fd, (struct sockaddr *) &addr, &size);

        if(client_fd != -1)
          handle_client(client_fd);
    } while(true);
    close(sock_fd);
    return EXIT_SUCCESS;
}
