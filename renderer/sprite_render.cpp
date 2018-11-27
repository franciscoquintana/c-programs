#include "sprite_render.h"

void printSpriteRotate(Sprite_Render render, int x_pos, int y_pos, Sprite sprite, int angulo) {
    if (angulo != 0) {
        Sprite temp;
        temp.x_offset = 0;
        temp.y_offset = 0;
        temp.image = rotate_png(sprite.image, angulo);

        printSprite(render, x_pos, y_pos, temp);

        free_image(temp.image);
    }
    else
        printSprite(render, x_pos, y_pos, sprite);
}

void printSprite(Sprite_Render render, int x_pos, int y_pos, Sprite sprite) {

    int height = (int) render.max_y < sprite.image.height ? render.max_y : sprite.image.height;
    int width = (int) render.max_x < sprite.image.width ? render.max_x : sprite.image.width;

    for(int y = sprite.y_offset; y < height; y++) {
        png_bytep row = sprite.image.rows[y];
        for(int x = sprite.x_offset; x < width; x++) {
            int location = (x + render.vinfo.xoffset + x_pos) * (render.vinfo.bits_per_pixel/8) +
                (y + render.vinfo.yoffset + y_pos) * render.finfo.line_length;
            png_bytep px = &(row[x * 4]);

            //Check if transparent
            if (px[0] == 0 && px[1] == 0 && px[2] == 0 && px[3] == 0)
                continue;

            *(render.fb_map + location) = px[2];        //Blue
            *(render.fb_map + location + 1) = px[1];     //Green
            *(render.fb_map + location + 2) = px[0];    //Red
            *(render.fb_map + location + 3) = 0;      // No transparency

        }
    }
}

Sprite load_sprite(char * filename) {
    Sprite sprite;
    sprite.image = read_png_file(filename);
    sprite.x_offset = 0;
    sprite.y_offset = 0;

    return sprite;
}

void init_sprite_render(Sprite_Render *render) {
    // Open the file for reading and writing
    int fd_fb = open("/dev/fb0", O_RDWR);
    if (fd_fb == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }

    // Get fixed screen information
    if (ioctl(fd_fb, FBIOGET_FSCREENINFO, &render->finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &render->vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    int screensize = render->vinfo.xres * render->vinfo.yres * (render->vinfo.bits_per_pixel / 8) * render->finfo.line_length;

    // Map the device to memory
    char * fb_map = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
    if (fb_map ==  (char *) -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

    render->fd_fb = fd_fb;
    //render->fb_real = fb_map;
    //render->fb_map = (char *) malloc(screensize);
    render->fb_map = fb_map;
    render->screensize = screensize;
    render->max_x = render->vinfo.xres;
    render->max_y = render->vinfo.yres;
}

void free_render(Sprite_Render *render) {
    munmap(render->fb_map, render->screensize);
    close(render->fd_fb);
}
