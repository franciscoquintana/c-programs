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

void init_font(Font *font_str, char *path) {
    size_t len;

	const char *fontPath = getenv("FONT");
	if (!fontPath) {
		fontPath = "Lat2-Terminus16.psfu.gz";
	}

	gzFile font = gzopen(fontPath, "r");
	if (!font) err(EX_NOINPUT, "%s", fontPath);

	PSF2Header header;
	len = gzfread(&header, sizeof(header), 1, font);
	if (!len && gzeof(font)) errx(EX_DATAERR, "%s: missing header", fontPath);
	if (!len) errx(EX_IOERR, "%s", gzerror(font, NULL));

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

        char glyphs[header.glyphCount][header.glyphSize];
	len = gzfread(glyphs, header.glyphSize, header.glyphCount, font);
	if (!len && gzeof(font)) errx(EX_DATAERR, "%s: missing glyphs", fontPath);
	if (!len) errx(EX_IOERR, "%s", gzerror(font, NULL));

	gzclose(font);

        unsigned short *unicode = (unsigned short*) calloc(USHRT_MAX, 2);
        char *buffer = (char*) malloc(USHRT_MAX * sizeof(char));

        int actual_glyph = 0;

        int len_unicode = gzread(font, buffer, USHRT_MAX);
        buffer = (char *) realloc(buffer, (len_unicode + 1) * sizeof(char));
        buffer[len_unicode] = '\0';
        
        while(strlen(buffer) != 0) {
            unsigned short uc = (unsigned short)buffer[0];
            if(uc == 0xFF) {
                actual_glyph++;
                buffer++;
                continue;
            } else if(uc & 128) {
                /* UTF-8 to unicode */
                if((uc & 32) == 0 ) {
                    uc = ((buffer[0] & 0x1F)<<6)+(buffer[1] & 0x3F);
                    buffer++;
                } else
                if((uc & 16) == 0 ) {
                    uc = ((((buffer[0] & 0xF)<<6)+(buffer[1] & 0x3F))<<6)+(buffer[2] & 0x3F);
                    buffer+=2;
                } else
                if((uc & 8) == 0 ) {
                    uc = ((((((buffer[0] & 0x7)<<6)+(buffer[1] & 0x3F))<<6)+(buffer[2] & 0x3F))<<6)+(buffer[3] & 0x3F);
                    buffer+=3;
                } else
                    uc = 0;
            }
            unicode[uc] = actual_glyph;
            buffer++;
        }

    font_str->header = header;

    font_str->glyphs = (int **) malloc(header.glyphCount * sizeof(int *));
    for(int i = 0; i < header.glyphCount; i++) {
        font_str->glyphs[i] = (int *) malloc(header.glyphSize *  sizeof(int));
        for(int g =0; g<header.glyphSize; g++)
            font_str->glyphs[i][g] = (int) glyphs[i][g];
    }
}



