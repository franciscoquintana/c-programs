#include "sprite_render.h"
#include "font_render.h"
#include "console.h"
#include "pthread.h"
#include <sys/time.h>
#include <math.h>
#include <signal.h>
#include <uuid/uuid.h>

#include "../common/common.h"
#include "../common/uuid_map.h"
#include "example.h"

UuidMap coches;
int finish_program;

uuid_t client_id;

void *render(void *param) {
    Sprite background = load_sprite((char *) "background.png");
    Sprite sprite = load_sprite((char *) "car.png");

    Sprite_Render render;

    init_sprite_render(&render);

    Font font;

    init_font(&font, (char *) "Lat2-Terminus16.psfu.gz");


    //    render.max_x = background.image.width;
    //    render.max_y = background.image.height;

    int now;
    int lastFrame = getTimeMs();

    int msMax = 1000/30;

    while(!finish_program) {
        now = getTimeMs();
        int delta = now - lastFrame;
        lastFrame = now;

        if (delta < msMax){
            usleep((msMax - delta) * 1000);
        }

        printSprite(render, 0, 0, background);

        for(int i = 0; i < coches.size; i++) {
            CarInfo coche = coches.map[i].value.info;;
            printSpriteRotate(render, coche.x, coche.y, sprite, coche.angle *180/3.141593 );
        }

        renderStr(render, font, 0, 0, "test");
    }

    free_render(&render);
    free_image(sprite.image);
    return NULL;
}

void int_handler(int sig) {
    finish_program = 1;
    reset_input_mode();
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

    init_uuid_map(&coches);

    if(error != -1) {
        Client client;

        client.moveinfo.down = 0; 
        client.moveinfo.left = 0;
        client.moveinfo.right = 0;
        client.moveinfo.up = 0;

        read(sock_fd, &client.info, sizeof(CarInfo));
        insert_uuid_map(&coches, client.info.id, client);

        memcpy(client_id, client.info.id, sizeof(uuid_t));

        return sock_fd;
    }
    else {
        fprintf(stderr,"Error al conectar al servidor\n");
        exit(1);
    }
}

void *listen(void *arg) {
    int server_fd = *(int *) arg;

    while(true) {
        CarInfo info;
        read(server_fd, &info, sizeof(CarInfo));
        Client *client = get_uuid_value(&coches, info.id);
        if (client != NULL)
            client->info = info;
        else {
            Client client;

            client.moveinfo.down = 0; 
            client.moveinfo.left = 0;
            client.moveinfo.right = 0;
            client.moveinfo.up = 0;
            client.info = info;
            insert_uuid_map(&coches, info.id, client);
        }

    }
}

int main() {
    atexit(&reset_input_mode);

    finish_program = 0;

    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = &int_handler;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);

    int server_fd = connect();

    pthread_t render_thread, keyboard_thread, listen_thread;

    set_input_mode();
    pthread_create(&render_thread, NULL, &render, NULL);

    pthread_create(&listen_thread, NULL, &listen, (void *) &server_fd);

    Sprite_Render render;
    init_sprite_render(&render);

    pthread_create(&keyboard_thread, NULL, &readKeyboard, NULL);

    int now;
    int lastFrame = getTimeMs();
    int msMax = 1000/30;

    Client *client = get_uuid_value(&coches, client_id);

    while(!(get_value(&mapKeys, KEY_CTRL) && get_value(&mapKeys, KEY_C))) {

        showCursor(false);

        now = getTimeMs();
        int delta = now - lastFrame;
        lastFrame = now;

        if (delta < msMax){
            usleep((msMax - delta) * 1000);
        }

        client->moveinfo.up = get_value(&mapKeys, KEY_W);
        client->moveinfo.left = get_value(&mapKeys, KEY_A);
        client->moveinfo.right = get_value(&mapKeys, KEY_D);
        client->moveinfo.down = get_value(&mapKeys, KEY_S);

    }
    reset_input_mode();

    pthread_join(keyboard_thread, NULL);
    pthread_join(render_thread, NULL);

    return 0;
}

