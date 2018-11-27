#ifndef __SPRITE_RENDER_H__
#define __SPRITE_RENDER_H__

#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <unistd.h>

#include "png.h"

typedef struct {
  Png_image image;
  int x_offset, y_offset;
} Sprite;

typedef struct {
  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo finfo;
  int fd_fb;
  int screensize;
  int max_x;
  int max_y;
  char *fb_map;
} Sprite_Render;

#ifdef __cplusplus
extern "C" {
#endif
    void printSprite(Sprite_Render render, int x_pos, int y_pos, Sprite sprite);
    void printSpriteRotate(Sprite_Render render, int x_pos, int y_pos, Sprite sprite, int angulo);
    Sprite load_sprite(char * filename);
    void init_sprite_render(Sprite_Render *render);
    void free_render(Sprite_Render *render);
#ifdef __cplusplus
}
#endif

#endif

