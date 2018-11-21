#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

struct prueba {
    int id;
    char array[16];
};

void function (int sh_id) {
    struct prueba* memoria = (struct prueba *) shmat (sh_id, NULL, 0);
    sleep(3);
    printf("Address: %i\n", sh_id);
    printf("Mato a el padre\n");
    memoria->id =50;   
    shmdt(memoria);
}

int main(){
    int shared_id = shmget(IPC_PRIVATE, sizeof(prueba), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    pid_t proceso = fork();
    if (proceso) {
        struct prueba* memoria= (struct prueba *) shmat (shared_id, NULL, 0);
        while(memoria->id != 50) {
            printf("Address: %i\n", shared_id);
            printf("Soy el padre y me estoy ejecutando%i\n", (*memoria).id);
            shmdt(&memoria);
        }
        printf("Me han matado\n");
        shmctl(shared_id, IPC_RMID,NULL);
    }
    else
        function(shared_id);

    return EXIT_SUCCESS;
}
