#include <unistd.h>
#include "png.h"

#define R 0
#define W 1

Png_image read_png_file(FILE *fp) {

  Png_image image;

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  image.width = png_get_image_width(png, info);
  image.height = png_get_image_height(png, info);
  png_byte color_type = png_get_color_type(png, info);
  png_byte bit_depth  = png_get_bit_depth(png, info);

  // Read any color_type into 8bit depth, RGBA format.
  // See http://www.libpng.org/pub/png/libpng-manual.txt

  if(bit_depth == 16)
    png_set_strip_16(png);

  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if(color_type == PNG_COLOR_TYPE_RGB ||
     color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  image.rows = (png_bytep*)malloc(sizeof(png_bytep) * image.height);
  for(int y = 0; y < image.height; y++) {
    image.rows[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
  }

  png_read_image(png, image.rows);

  fclose(fp);

  //Libera recursos
  png_destroy_read_struct(&png, &info, NULL);

  return image;
}

Png_image read_png_file(char *filename) {
  FILE *fp = fopen(filename, "rb");
  return read_png_file(fp);
}

void write_png(int fd, Png_image image) {
  FILE *fp = fdopen(fd, "wb");
  if(!fp) abort();

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) abort();

  png_infop info = png_create_info_struct(png);
  if (!info) abort();

  if (setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR(
    png,
    info,
    image.width, image.height,
    8,
    PNG_COLOR_TYPE_RGBA,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);

  png_write_image(png, image.rows);
  png_write_end(png, NULL);

  fclose(fp);

  if (png && info)
        png_destroy_write_struct(&png, &info);
}

Png_image rotate_png(Png_image original, int grados) {
    int fd[2][2];

    pipe(fd[0]);
    pipe(fd[1]);

    //prepare_handler_child();

    pid_t convert_id = fork();

    if(convert_id > 0) {
        close(fd[0][R]);
        close(fd[1][W]);

        write_png(fd[0][W], original);

        //Cerramos la pipe para que el sort sepa que hemos terminado de escribir
        close(fd[0][W]);

        FILE *fp = fdopen(fd[1][R], "rb");
        Png_image image = read_png_file(fp);

        close(fd[1][R]);

	return image;

    }
    else {

        close(fd[0][W]);
        close(fd[1][R]);

        dup2(fd[0][R], STDIN_FILENO);
        dup2(fd[1][W], STDOUT_FILENO);
        
        char gradosStr[3];

        sprintf(gradosStr, "%i", grados);

        execlp("convert", "convert", "-background", "rgba(0,0,0,0)", "-rotate", gradosStr, "-", "-", NULL);

        fprintf(stderr, "No se ha iniciado convert\n");

        close(fd[0][R]);
        close(fd[1][W]);

        abort();

    }
}

void free_image(Png_image image) {
  free(image.rows);
}
