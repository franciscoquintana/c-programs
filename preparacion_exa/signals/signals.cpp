#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>

int close_p = 0;

void handler(int sig) {
    close_p = 1;

    printf("Nos vamos a cerrar, deberiamos cerrar los sockets\n");
}

int main(){
    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = &handler;

    sigaction(SIGINT, &sa, NULL);
    printf("%i\n", getpid());
    while(!close_p) {

    }
    return EXIT_SUCCESS;
}
