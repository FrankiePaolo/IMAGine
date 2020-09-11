#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#  include <vips/vips.h>
#  include "utils.h"
#  include "imageops.h"

/* This sometimes causes memory issues, needs to be updated */
void
openImg(char * path){
   char * open = strdup("xdg-open ");     
   char * command; 

   command=strcat(open,path);
   system(command);
}

/* Returns the number of pixels across the image */
struct utils *
getWidth(struct symref * v) {
   int val;
   struct utils * temp1 = v -> s -> value;
   val=vips_image_get_width(((struct img * ) temp1) -> img);
   return ((struct utils *)newint(val,'+'));
}

/* Returns the number of pixels down the image */
struct utils *
getHeight(struct symref * v) {
   int val;
   struct utils * temp1 = v -> s -> value;
   val=vips_image_get_height(((struct img * ) temp1) -> img);
   return ((struct utils *)newint(val,'+'));
}

/* Returns the number of bands(channels) in the image */
struct utils *
getBands(struct symref * v) {
   int val;
   struct utils * temp1 = v -> s -> value;
   val=vips_image_get_bands(((struct img * ) temp1) -> img);
   return ((struct utils *)newint(val,'+'));
}

/* Returns the minimum value in an image */
struct utils *
min(struct symref * v) {
   double min;
   struct utils * temp1 = v -> s -> value;
   if (vips_min((((struct img * ) temp1) -> img), & min, NULL)) {
      vips_error_exit(NULL);
   }
   return ((struct utils *)newdouble(min,'+'));
}

/* Returns the maximum value in an image */
struct utils *
max(struct symref * v) {
   double max;
   struct utils * temp1 = v -> s -> value;
   if (vips_max((((struct img * ) temp1) -> img), & max, NULL)) {
      vips_error_exit(NULL);
   }
   return ((struct utils *)newdouble(max,'+'));
}

/* Returns the average value in an image */
struct utils *
average(struct symref * v) {
   double mean;
   struct utils * temp1 = v -> s -> value;
   if (vips_avg((((struct img * ) temp1) -> img), & mean, NULL)) {
      vips_error_exit(NULL);
   }
   return ((struct utils *)newdouble(mean,'+'));
}

/* Returns the inverted image and saves it in "output_path" */
struct utils * 
invert(struct symref * l,struct ast * v) {
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_invert((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

/* Returns the input image but moves it to differt space and saves it in "output_path" */
struct utils * 
toColorSpace(struct symref * l,struct ast * v,struct ast * s){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   VipsInterpretation in_space=vips_image_guess_interpretation(((struct img * ) temp1) -> img);
   VipsInterpretation out_space=getSpace(s);
   (((struct img * ) temp1) -> img)->Type=in_space;

   if (vips_colourspace((((struct img * ) temp1) -> img), & out,  out_space,NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   

   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}



struct utils * 
crop(struct symref * l,struct symref * r,struct ast * left,struct ast * top,struct ast * width,struct ast * height){
   VipsImage * out;
   char * path;
   double left_value=getValue(left);
   double top_value=getValue(top);
   double width_value=getValue(width);
   double height_value=getValue(height);
   struct utils * temp1 = l -> s -> value;
   if (vips_crop((((struct img * ) temp1) -> img), & out,left_value,top_value,width_value,height_value, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath( ((struct ast *) r) );
   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

void
saveImage(char * in, VipsImage * out, char * path){
   char * suffix=getFormat(strdup(path));
   char * temp=strdup(".");

   if(suffix==NULL){
      path=strcat(path, temp);
      path=strcat(path, getFormat(in));

      saveImage(in, out, path);
   } else{
      if((strcmp(suffix, "png"))==0){
         yyerror("PNG is unfortunatly not supported by our lib! See you soon!");
         exit(0);
      } else if((strcmp(suffix, "tif"))==0){
         if (vips_tiffsave(out, path, NULL)) {
            vips_error_exit(NULL);
         }
      } else if( ((strcmp(suffix, "jpeg"))==0) || ((strcmp(suffix, "jpg"))==0) ){
         if (vips_jpegsave(out, path, NULL)) {
            vips_error_exit(NULL);
         }
      } else if((strcmp(suffix, "hdr"))==0){
         if (vips_radsave(out, path, NULL)) {
            vips_error_exit(NULL);
         }
      } else if((strcmp(suffix, "raw"))==0){
         if (vips_rawsave(out, path, NULL)) {
            vips_error_exit(NULL);
         }
      } else{         
         path=strcat(path, temp);
         path=strcat(path, getFormat(in));

         saveImage(in, out, path);
      }      
   }
}



struct utils * 
convert(struct symref * l,struct ast * v) {
   struct utils * temp1 = l -> s -> value;
   VipsImage * in = ((struct img * ) temp1) -> img;
   VipsImage * out;
   char * path;
   path=getPath(v);
   vips_copy(in, &out, NULL);
   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}



struct utils * 
smartCrop(struct symref * l,struct symref * r,struct ast * width,struct ast * height){
   VipsImage * out;
   char * path;
   double width_value=getValue(width);
   double height_value=getValue(height);
   struct utils * temp1 = l -> s -> value;

   if (vips_smartcrop((((struct img * ) temp1) -> img), & out, width_value, height_value, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath( ((struct ast *) r) );

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}


struct utils * 
zoom(struct symref * l,struct symref * r,struct ast * xfactor,struct ast * yfactor){
   VipsImage * out;
   char * path;
   int x=(int) getValue(xfactor);
   int y=(int) getValue(yfactor);
   struct utils * temp1 = l -> s -> value;

   if (vips_zoom((((struct img * ) temp1) -> img), & out, x, y, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath( ((struct ast *) r) );

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils * 
add(struct symref * l,struct symref * r,struct ast * p){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l-> s -> value;
   struct utils * temp2 = r-> s -> value;

   if (vips_add((((struct img * ) temp1) -> img),(((struct img * ) temp2) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(p);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   

   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils * 
subtract_img(struct symref * l,struct symref * r,struct ast * p){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l-> s -> value;
   struct utils * temp2 = r-> s -> value;

   if (vips_subtract((((struct img * ) temp1) -> img),(((struct img * ) temp2) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(p);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   

   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}


struct utils *
flip(struct symref * l,struct ast * v,struct ast * s){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   char * str=getPath(s);
   VipsDirection direction;

   if(!strcmp(str,"hor")){
      direction=VIPS_DIRECTION_HORIZONTAL;   
   }else if(!strcmp(str,"ver")){
      direction=VIPS_DIRECTION_VERTICAL;
   }else{
      printf("Third parameter error, need to be 'hor' or 'ver'!\n");
      exit(0);
   }

   if (vips_flip((((struct img * ) temp1) -> img), & out, direction, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils *
rotate(struct symref * l,struct ast * v,struct ast * s){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   double angle=getValue(s);

   if (vips_rotate((((struct img * ) temp1) -> img), & out, angle, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}


struct utils *
histeq(struct symref * l,struct ast * v){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_hist_equal((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils *
norm(struct symref * l,struct ast * v){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_hist_norm((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils *
gaussianBlur(struct symref * l,struct ast * v,struct ast * s){
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   double sigma=getValue(s);

   if (vips_gaussblur((((struct img * ) temp1) -> img), & out, sigma, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils * 
canny(struct symref * l,struct ast * v) {
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_canny((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils * 
sobel(struct symref * l,struct ast * v) {
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_sobel((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}

struct utils * 
sharpen(struct symref * l,struct ast * v) {
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_sharpen((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   saveImage(((struct img * ) temp1) ->path, out, path);
   printf("Image saved in '%s'\n", path);
   
   
   struct img * a = malloc(sizeof(struct img));
   a -> nodetype = 'P'; //P as in picture
   a -> path = path;
   a -> img = out;
   return ((struct utils *)a);
}