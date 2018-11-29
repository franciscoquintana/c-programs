#include <getopt.h>
#include <signal.h>
#include <sys/wait.h>
#include <math.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "../common/common.h"
#include "../common/uuid_map.h"

UuidMap *clientMap;

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

void moveCoche(CarInfo *coche)
{
    coche->x += sin(coche->angle) * coche->speed;
    coche->y -= cos(coche->angle) * coche->speed;

    if (coche->x < 0)
        coche->x = 0;

    if (coche->y < 0)
        coche->y = 0;
}

void partida_run() {
    float maxSpeed = 12.0;
    float acc=0.2, dec=0.3;
    float turnSpeed= 0.08;

    int now;
    int lastFrame = getTimeMs();
    int msMax = 1000/30;


    printf("%i\n", getpid());
    while(true) {
        now = getTimeMs();
        int delta = now - lastFrame;
        lastFrame = now;

        if (delta < msMax){
            usleep((msMax - delta) * 1000);
        }

        for (int c=0; c<clientMap->size ;c++) {
            Client *client = &clientMap->map[c].value;
            if (client->moveinfo.up && client->info.speed<maxSpeed)
                client->info.speed += client->info.speed < 0 ? dec :  acc;

            if (client->moveinfo.down && client->info.speed>-maxSpeed)
                client->info.speed -= client->info.speed > 0 ? dec : acc;

            if (!client->moveinfo.up && !client->moveinfo.down)
                if (client->info.speed - dec > 0) 
                    client->info.speed -= dec;
                else if (client->info.speed + dec < 0) 
                    client->info.speed += dec;
                else 
                    client->info.speed = 0;

            if (client->info.speed != 0) {
                if (client->moveinfo.right)
                    client->info.angle += turnSpeed * client->info.speed/maxSpeed;
                if (client->moveinfo.left)
                    client->info.angle -= turnSpeed * client->info.speed/maxSpeed;
            }

            if (client->info.angle > 360)
                client->info.angle = 0;

            moveCoche(&client->info);
        }
    }

}

void handle_client(int client_fd) {
    fprintf(stderr,"%i\n", getpid());
    //sleep(10);
    Client client;

    client.info.x = 200;
    client.info.y = 200;
    client.info.speed = 0;
    client.info.angle = 0;

    client.moveinfo.down = 0;
    client.moveinfo.left = 0;
    client.moveinfo.right = 0;
    client.moveinfo.up = 0;

    client.fd = client_fd;

    uuid_generate_random(client.info.id);

    write(client_fd, &client.info, sizeof(CarInfo));

    insert_uuid_map(clientMap, client.info.id, client);

    //!Desconectado
    while (true) {
        Client * client_2 = get_uuid_value(clientMap, client.info.id);
        read(client_fd, &client_2->moveinfo, sizeof(MoveCar));
        for (int c=0; c<clientMap->size ;c++) {
           Client *client = &clientMap->map[c].value;
           write(client->fd, &client->info, sizeof(CarInfo));       
         }
    }
}

void init_server(int loopback, int port) {
    pthread_t hilo;
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

    listen(sock_fd, 2);

//MAP MEMORY
    int shared_id = shmget(IPC_PRIVATE, sizeof(UuidMap), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    clientMap =(UuidMap *) shmat (shared_id, NULL, 0);
    init_uuid_map(clientMap);

    pid_t partida = fork();
    if (partida == 0) {
        partida_run();
        exit(0);
    }

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
                close(client_fd);
                exit(0);
            }
        }
        //Poner una condición de salida ?
    } while(true);
    close(sock_fd);
}

int main (int argc, char* argv[])
{
    int option;
    int loopback = 0;
    int port = 8888;

    const char * const sh_options = "p:";
    const struct option l_options[] = {
        { "port", 1, NULL, 'p' },
        {NULL, 0, NULL, 0}
    };
    do {
        option = getopt_long(argc, argv, sh_options, l_options, NULL);

        switch(option) {
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
