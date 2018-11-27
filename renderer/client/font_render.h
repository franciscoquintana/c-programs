#ifndef __FONT_RENDER_H__
#define __FONT_RENDER_H__

#include <err.h>
#include <zlib.h>
#include <sysexits.h>
#include <string.h>
#include "sprite_render.h"

typedef struct{
    int magic;
    int version;
    int headerSize;
    int flags;
    int glyphCount;
    int glyphSize;
    int glyphHeight;
    int glyphWidth;
} PSF2Header;

typedef struct {
    PSF2Header header;
    int **glyphs;
} Font;

#ifdef __cplusplus
extern "C" {
#endif
    extern int PSF2Magic;
    void renderStr(Sprite_Render render, Font font, int init_x, int init_y, const char *s);
    void init_font(Font *font, char *path);
#ifdef __cplusplus
}
#endif

#endif

