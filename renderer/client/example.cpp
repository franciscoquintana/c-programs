#include "sprite_render.h"
#include "font_render.h"
#include "console.h"
#include "pthread.h"
#include <sys/time.h>
#include <math.h>
#include <signal.h>

#include "example.h"

int finish_program;

typedef struct {
    int x,y;
    float speed, angle;
} Coche;

Coche *coches;
int numCoches;

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

    //printSprite(render, 0, 0, background);

    while(!finish_program) {
        now = getTimeMs();
        int delta = now - lastFrame;
        lastFrame = now;

        if (delta < msMax){
            usleep((msMax - delta) * 1000);
        }

        printSprite(render, 0, 0, background);

        for(int i = 0; i < numCoches; i++) {
            Coche coche = coches[i];
            printSpriteRotate(render, coche.x, coche.y, sprite, coche.angle *180/3.141593 );
        }

        renderStr(render, font, 0, 0, "test");
    }

    free_render(&render);
    free_image(sprite.image);
    return NULL;
}

void moveCoche(Coche *coche, Sprite_Render render)
{
    coche->x += sin(coche->angle) * coche->speed;
    coche->y -= cos(coche->angle) * coche->speed;

    if (coche->x < 0)
        coche->x = 0;

    if (coche->y < 0)
        coche->y = 0;
}

void int_handler(int sig) {
    finish_program = 1;
    reset_input_mode();
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

    float maxSpeed = 12.0;
    float acc=0.2, dec=0.3;
    float turnSpeed= 0.08;

    numCoches = 1;
    coches =(Coche *) malloc(sizeof(Coche) ) ;

    Coche coche;
    coche.x = 220;
    coche.y = 220;
    coche.speed = 0;
    coche.angle = 0;

    coches[0] = coche;

    pthread_t render_thread, keyboard_thread;
    pthread_create(&render_thread, NULL, &render, NULL);

    set_input_mode();

    Sprite_Render render;
    init_sprite_render(&render);

    pthread_create(&keyboard_thread, NULL, &readKeyboard, NULL);

    int now;
    int lastFrame = getTimeMs();
    int msMax = 1000/30;

    int up, left, right, down;

    while(!(get_value(&mapKeys, KEY_CTRL) && get_value(&mapKeys, KEY_C))) {

        showCursor(false);

        now = getTimeMs();
        int delta = now - lastFrame;
        lastFrame = now;

        if (delta < msMax){
            usleep((msMax - delta) * 1000);
        }

        up = get_value(&mapKeys, KEY_W);
        left = get_value(&mapKeys, KEY_A);
        right = get_value(&mapKeys, KEY_D);
        down = get_value(&mapKeys, KEY_S);

        if (up && coche.speed<maxSpeed)
            coche.speed += coche.speed < 0 ? dec :  acc;

        if (down && coche.speed>-maxSpeed)
            coche.speed -= coche.speed > 0 ? dec : acc;

        if (!up && !down)
          if (coche.speed - dec > 0) 
            coche.speed -= dec;
          else if (coche.speed + dec < 0) 
            coche.speed += dec;
          else 
          coche.speed = 0;

        if (coche.speed != 0) {
            if (right)
                coche.angle += turnSpeed * coche.speed/maxSpeed;
            if (left)
                coche.angle -= turnSpeed * coche.speed/maxSpeed;
        }

        if (coche.angle > 360)
            coche.angle = 0;

        moveCoche(&coche, render);

        coches[0] = coche;
    }

    reset_input_mode();

    pthread_join(keyboard_thread, NULL);
    pthread_join(render_thread, NULL);
    
    return 0;
}

