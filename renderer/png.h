#ifndef __PNG_H__
#define __PNG_H__

#include <stdlib.h>
#include <png.h>

typedef struct {
  int width, height;
  png_bytep *rows;
} Png_image;

#ifdef __cplusplus
extern "C" {
#endif
    Png_image read_png_file(char *filename);
    void write_png(int fd, Png_image image);
    Png_image rotate_png(Png_image original, int grados);
    void free_image(Png_image image);
#ifdef __cplusplus
}
#endif

#endif
