#include <getopt.h>
#include <signal.h>
#include <sys/wait.h>
#include "common.h"

#define R 0
#define W 1

void handle_client(int client_fd) {
    int fd[2][2];

    pipe(fd[0]);
    pipe(fd[1]);

    pid_t sort_id = fork();

    if(sort_id > 0) {
        close(fd[0][R]);
        close(fd[1][W]);

        //Abrimos la pipe de lectura
        FILE *stream_sort = fdopen(fd[1][R], "r");

        char * palabras = leeStr(client_fd);
        write(fd[0][W], palabras, sizeof(palabras));
        free(palabras);

        char buffer[GRANDE];
        fscanf(stream_sort, "%s", buffer);
        enviaStr(client_fd, buffer);

    }
    else {

        close(client_fd);
        close(fd[0][W]);
        close(fd[1][R]);

        dup2(fd[0][R], STDIN_FILENO);
        dup2(fd[1][W], STDOUT_FILENO);

        execlp("sort", "sort", NULL);

        fprintf(stderr, "No se ha iniciado sort\n");

        close(fd[0][R]);
        close(fd[1][W]);

        abort();

    }
}

void init_server(int loopback, int port) {
    int sock_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(loopback ? INADDR_LOOPBACK : INADDR_ANY);

    int error = bind(sock_fd,(struct sockaddr *) &addr, sizeof(addr));

    if(error != 0) {
        fprintf(stderr,"Failed to bind\n");
        exit(1);
    }

    listen(sock_fd, 1);

    do {
        socklen_t size = sizeof(addr);

        int client_fd = accept(sock_fd, (struct sockaddr *) &addr, &size);

        if(client_fd != -1) {
            pid_t hijo_id = fork();
            //Somos el padre a si que cerramos el fd del cliente
            if(hijo_id > 0) {
                close(client_fd);
            }
            else {
                //Cerramos el fd del socket
                close (STDIN_FILENO);
                close (STDOUT_FILENO);
                handle_client(client_fd);
                close (sock_fd);
            }
        }

    } while(true);
    close(sock_fd);
}

void clean_child(int signal) {
    int code;
    wait(&code);
}

void prepare_handler_child() {
    struct sigaction sigchld_act;

    memset(&sigchld_act, 0, sizeof(sigchld_act));
    sigchld_act.sa_handler = &clean_child;
    sigaction(SIGCHLD, &sigchld_act, NULL);
}

int main (int argc, char* argv[])
{
    int option;
    int loopback = 0;
    int port = 8888;

    const char * const sh_options = "lp:";
    const struct option l_options[] = {
        { "loopback", 0, NULL, 'l' },
        { "port", 1, NULL, 'p' },
        {NULL, 0, NULL, 0}
    };
    do {
        option = getopt_long(argc, argv, sh_options, l_options, NULL);

        switch(option) {
            case 'l':
                loopback = 1;
                break;
            case 'p':
                sscanf(optarg, "%i", &port);
                break;
            case -1:
              break;
        }
    } while(option != -1);

    prepare_handler_child();

    printf("Iniciando servidor en el puerto %i\n", port);
    init_server(loopback, port);
}
