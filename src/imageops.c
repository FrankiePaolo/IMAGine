#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "vips/vips.h"
#include "utils.h"
#include "imageops.h"

#if defined(__linux__)
    #define OS 2
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS 1
#else
    #define OS 0
#endif

/* Returns the number of pixels across the image */
struct utils *
   getWidth(struct symref * v) {
      int val;
      struct utils * temp1 = takeImage(v);
      val = vips_image_get_width(((struct img * ) temp1) -> img);
      return ((struct utils * ) newint(val, '+'));
   }

/* Returns the number of pixels down the image */
struct utils *
   getHeight(struct symref * v) {
      int val;
      struct utils * temp1 = takeImage(v);
      val = vips_image_get_height(((struct img * ) temp1) -> img);
      return ((struct utils * ) newint(val, '+'));
   }

/* Returns the number of bands(channels) in the image */
struct utils *
   getBands(struct symref * v) {
      int val;
      struct utils * temp1 = takeImage(v);
      val = vips_image_get_bands(((struct img * ) temp1) -> img);
      return ((struct utils * ) newint(val, '+'));
   }

/* Returns the minimum value in an image */
struct utils *
   min(struct symref * v) {
      double min;
      struct utils * temp1 = takeImage(v);
      if (vips_min((((struct img * ) temp1) -> img), & min, NULL)) {
         vips_error_exit(NULL);
      }
      return ((struct utils * ) newdouble(min, '+'));
   }

/* Returns the maximum value in an image */
struct utils *
   max(struct symref * v) {
      double max;
      struct utils * temp1 = takeImage(v);
      if (vips_max((((struct img * ) temp1) -> img), & max, NULL)) {
         vips_error_exit(NULL);
      }
      return ((struct utils * ) newdouble(max, '+'));
   }

/* Returns the average value in an image */
struct utils *
   average(struct symref * v) {
      double mean;
      struct utils * temp1 = takeImage(v);
      if (vips_avg((((struct img * ) temp1) -> img), & mean, NULL)) {
         vips_error_exit(NULL);
      }
      return ((struct utils * ) newdouble(mean, '+'));
   }

/* Returns the inverted image and saves it in "output_path" */
struct utils *
   invert(struct symref * l, struct ast * v) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      if (vips_invert((((struct img * ) temp1) -> img), & out, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);
      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Returns the input image with an equalized histogram and saves it in "output_path" */
struct utils *
   histeq(struct symref * l, struct ast * v) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      if (vips_hist_equal((((struct img * ) temp1) -> img), & out, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Returns the input image with a normalized histogram and saves it in "output_path" */
struct utils *
   norm(struct symref * l, struct ast * v) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      if (vips_hist_norm((((struct img * ) temp1) -> img), & out, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Finds the edge in the input image with the Canny method,returns it and saves it in "output_path" */
struct utils *
   canny(struct symref * l, struct ast * v) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      if (vips_canny((((struct img * ) temp1) -> img), & out, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Finds the edges in the input image with the Sobel edge detector method, returns it and saves it in "output_path" */
struct utils *
   sobel(struct symref * l, struct ast * v) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      if (vips_sobel((((struct img * ) temp1) -> img), & out, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Performs a gaussian blur and subtracts it from the input image to generate a high-frequency signal, returns it and saves it in "output_path" */
struct utils *
   sharpen(struct symref * l, struct ast * v) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      if (vips_sharpen((((struct img * ) temp1) -> img), & out, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Returns the converted input image with the specified format in "output_path" and saves it in "output_path" */
struct utils *
   convert(struct symref * l, struct ast * v) {
      struct utils * temp1 = takeImage(l);
      VipsImage * in = ((struct img * ) temp1) -> img;
      VipsImage * out;
      char * path;
      path = getPath(v);
      vips_copy( in , & out, NULL);
      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);
      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Returns the input image but moves it to differt color space and saves it in "output_path" */
struct utils *
   toColorSpace(struct symref * l, struct ast * v, struct ast * s) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      VipsInterpretation in_space = vips_image_guess_interpretation(((struct img * ) temp1) -> img);
      VipsInterpretation out_space = getSpace(s);
      (((struct img * ) temp1) -> img) -> Type = in_space;

      if (vips_colourspace((((struct img * ) temp1) -> img), & out, out_space, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Returns the bitwise sum of the pixels of the 2 images and saves it in "output_path" */
struct utils *
   add(struct symref * l, struct symref * r, struct ast * p) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      struct utils * temp2 = takeImage(r);

      if (vips_add((((struct img * ) temp1) -> img), (((struct img * ) temp2) -> img), & out, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(p);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Returns the bitwise difference of the pixels of the 2 images and saves it in "output_path" */
struct utils *
   subtract_img(struct symref * l, struct symref * r, struct ast * p) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      struct utils * temp2 = takeImage(r);

      if (vips_subtract((((struct img * ) temp1) -> img), (((struct img * ) temp2) -> img), & out, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(p);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Returns the rotated input image by the rotate_angle and saves it in "output_path" */
struct utils *
   rotate(struct symref * l, struct ast * v, struct ast * s) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      double angle = getValue(s);

      if (vips_rotate((((struct img * ) temp1) -> img), & out, angle, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Returns the flipped input image with the specified direction and saves it in "output_path" */
struct utils *
   flip(struct symref * l, struct ast * v, struct ast * s) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      char * str = getPath(s);
      VipsDirection direction;

      if (!strcmp(str, "hor")) {
         direction = VIPS_DIRECTION_HORIZONTAL;
      } else if (!strcmp(str, "ver")) {
         direction = VIPS_DIRECTION_VERTICAL;
      } else {
         yyerror("Third parameter error, needs to be 'hor' or 'ver'!");
      }

      if (vips_flip((((struct img * ) temp1) -> img), & out, direction, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Returns the blurred input image with a gaussian mask of size mask_dim and saves it in "output_path" */
struct utils *
   gaussianBlur(struct symref * l, struct ast * v, struct ast * s) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      double sigma = getValue(s);

      if (vips_gaussblur((((struct img * ) temp1) -> img), & out, sigma, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Extract a band from the input image, counts from 0 to 2 and saves it in "output_path" */
struct utils *
   extractBand(struct symref * l, struct ast * v, struct ast * s) {
      VipsImage * out;
      char * path;
      struct utils * temp1 = takeImage(l);
      int band = (int) getValue(s);

      if (band < 0 || band > 2) {
         yyerror("Need to insert a band value from 0 to 2!");
      }

      if (vips_extract_band((((struct img * ) temp1) -> img), & out, band, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(v);

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Crops an image down to specified width and height by removing the boring parts(it looks for features likely to draw human attention), returns it and saves it in "output_path" */
struct utils *
   smartCrop(struct symref * l, struct symref * r, struct ast * width, struct ast * height) {
      VipsImage * out;
      char * path;
      double width_value = getValue(width);
      double height_value = getValue(height);
      struct utils * temp1 = takeImage(l);

      if (vips_smartcrop((((struct img * ) temp1) -> img), & out, width_value, height_value, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(((struct ast * ) r));

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Returns the zoomed input image by repeating pixels. This is fast nearest-neighbour zoom. It saves it in "output_path" */
struct utils *
   zoom(struct symref * l, struct symref * r, struct ast * xfactor, struct ast * yfactor) {
      VipsImage * out;
      char * path;
      int x = (int) getValue(xfactor);
      int y = (int) getValue(yfactor);
      struct utils * temp1 = takeImage(l);

      if (vips_zoom((((struct img * ) temp1) -> img), & out, x, y, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(((struct ast * ) r));

      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);

      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Extract an area with coordinates left, top and of size width, height from an image ,returns it and saves it in "output_path" */
struct utils *
   crop(struct symref * l, struct symref * r, struct ast * left, struct ast * top, struct ast * width, struct ast * height) {
      VipsImage * out;
      char * path;
      double left_value = getValue(left);
      double top_value = getValue(top);
      double width_value = getValue(width);
      double height_value = getValue(height);
      struct utils * temp1 = takeImage(l);
      if (vips_crop((((struct img * ) temp1) -> img), & out, left_value, top_value, width_value, height_value, NULL)) {
         vips_error_exit(NULL);
      }
      path = getPath(((struct ast * ) r));
      saveImage(((struct img * ) temp1) -> path, out, path);
      printf("Image saved in '%s'\n", path);
      struct img * a = malloc(sizeof(struct img));
      a -> nodetype = 'P';
      a -> path = path;
      a -> img = out;
      return ((struct utils * ) a);
   }

/* Saves the image in the given path, if the user doesn't give the format or if it's wrong, it's deduced from the input image  */
void
saveImage(char * in , VipsImage * out, char * path) {
   char * suffix = getFormat(strdup(path));
   char * temp = strdup(".");

   if (suffix == NULL) {
      path = strcat(strdup(path), temp);
      path = strcat(strdup(path), getFormat( in ));

      saveImage( in , out, path);
   } else {
      if ((strcmp(suffix, "png")) == 0) {
         yyerror("PNG is unfortunatly not supported by our lib! See you soon!");
      } else if ((strcmp(suffix, "tif")) == 0) {
         if (vips_tiffsave(out, path, NULL)) {
            vips_error_exit(NULL);
         }
      } else if (((strcmp(suffix, "jpeg")) == 0) || ((strcmp(suffix, "jpg")) == 0)) {
         if (vips_jpegsave(out, path, NULL)) {
            vips_error_exit(NULL);
         }
      } else if ((strcmp(suffix, "hdr")) == 0) {
         if (vips_radsave(out, path, NULL)) {
            vips_error_exit(NULL);
         }
      } else if ((strcmp(suffix, "raw")) == 0) {
         if (vips_rawsave(out, path, NULL)) {
            vips_error_exit(NULL);
         }
      } else {
         path = strcat(strdup(path), temp);
         path = strcat(strdup(path), getFormat( in ));

         saveImage( in , out, path);
      }
   }
}

/* Shows the given image */
void
showImg(struct symref * l) {
   char * command;
   switch (OS) {
   case 1:
      asprintf( & command, "open %s", ((struct img * ) takeImage(l)) -> path);
      break;
   case 2:
      asprintf( & command, "mimeopen %s", ((struct img * ) takeImage(l)) -> path);
      break;
   default:
      printf("Function not supported in this OS\n");
      return;
   }
   system(command);
   free(command);
}