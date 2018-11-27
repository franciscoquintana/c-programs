#include "font_render.h"

int PSF2Magic = 0x864AB572;

void renderChar(Sprite_Render render, Font font, int init_x, int init_y, char c) {
    int *glyph = font.glyphs[(unsigned) c];
    int stride = font.header.glyphSize / font.header.glyphHeight;
    for (int y = 0; y < font.header.glyphHeight; ++y) {
        for (int x = 0; x < font.header.glyphWidth; ++x) {
            int bits = glyph[y * stride + x / 8];
            int bit = bits >> (7 - x % 8) & 1;
            //render.fb_map[(init_y + y) *  init_x + x] = bit ? (char) 0xFF : 0x000000;
           int location = (x + render.vinfo.xoffset + init_x) * (render.vinfo.bits_per_pixel/8) +
                (y + render.vinfo.yoffset + init_y) * render.finfo.line_length;

            *(render.fb_map + location) = 0;        //Blue
            *(render.fb_map + location + 1) = 0;     //Green
            *(render.fb_map + location + 2) = bit ? 0xFF : 0x00;    //Red
            *(render.fb_map + location + 3) = 0;      // No transparency
        }
    }
}

void renderStr(Sprite_Render render, Font font, int init_x, int init_y, const char *s) {
    for (; *s; ++s) {
        renderChar(render, font, init_x, init_y, *s);
        init_x += font.header.glyphWidth;
    }
}

void init_font(Font *font, char *path) {
    size_t len;

    const char *fontPath = getenv("FONT");
    if (!fontPath) {
        fontPath = path;
    }

    gzFile fontFile = gzopen(fontPath, "r");
    if (!font) err(EX_NOINPUT, "%s", fontPath);

    PSF2Header header;
    len = gzfread(&header, sizeof(header), 1, fontFile);
    if (!len && gzeof(fontFile)) errx(EX_DATAERR, "%s: missing header", fontPath);
    if (!len) errx(EX_IOERR, "%s", gzerror(fontFile, NULL));

    if (header.magic != PSF2Magic) {
        errx(
                EX_DATAERR, "%s: invalid header magic %08X",
                fontPath, header.magic
            );
    }
    if (header.headerSize != sizeof(PSF2Header)) {
        errx(
                EX_DATAERR, "%s: weird header size %d",
                fontPath, header.headerSize
            );
    }

    int glyphs[128][header.glyphSize];
    len = gzfread(glyphs, header.glyphSize, 128, fontFile);
    if (!len && gzeof(fontFile)) errx(EX_DATAERR, "%s: missing glyphs", fontPath);
    if (!len) errx(EX_IOERR, "%s", gzerror(fontFile, NULL));

    gzclose(fontFile);

    font->header = header;

    font->glyphs = (int **) malloc(128 * sizeof(int *));
    for(int i = 0; i < 128; i++) {
        font->glyphs[i] = (int *) malloc(header.glyphSize *  sizeof(int));
        memcpy(font->glyphs[i], glyphs[i], sizeof(int) * header.glyphSize);
    }
}



