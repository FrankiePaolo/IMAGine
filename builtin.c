#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#  include <vips/vips.h>
#  include "utils.h"
#  include "builtin.h"
#  include "eval.h"

struct utils *
   callbuiltin(struct fncall * f) {
      enum bifs functype = f -> functype;
      struct utils * v = eval(f -> l);     
      // Find tree node

      switch (functype) {
      case b_print:
         print_B(v);
         return v;
      case b_width:
         getWidth(((struct symref * ) v));
         return v;
      case b_height:
         getHeight(((struct symref * ) v));
         return v;
      case b_bands:
         getBands(((struct symref * ) v));
         return v;
      case b_crop:
         crop(((struct symref *)f->l->l),f->l->r->l,f->l->r->r->l,f->l->r->r->r->l,f->l->r->r->r->r->l,v);
         return v;
      case b_add:
         add(((struct symref *)f->l->l),f->l->r->l,v);
         return v;
      case b_subtract:
         subtract_img(((struct symref *)f->l->l),f->l->r->l,v);
         return v;
      case b_convert:
         toColorSpace(((struct symref *)f->l->l),f->l->r->l,v);
         return v;
      case b_invert:
         invert(((struct symref *)f->l->l),v);
         return v;
      case b_average:
         average(((struct symref * ) v));
         return v;
      case b_get:
         get( ((struct symref *)f->l->l)->s,v);
         return v;
      case b_push:
         push( ((struct symref *)f->l->l)->s,v);
         return v;
      case b_pop:
         pop( ((struct symref * ) v)->s );
         return v;
      case b_depth:
         return depth( ((struct symref * ) v)->s );
      default:
         yyerror("Unknown built-in function %d", functype);
         return NULL;
      }
   }

/* methods for lists */
struct utils * 
depth(struct symbol * e){
   struct utils * v;
   struct list * temp = e->li;
   int counter=1;

   if(!temp && (e->value)){
      yyerror("The list does not exist\n");
      return NULL;
   }

   if(!temp){
      v=((struct utils *)newint(0,'+'));
      return v;
   }

   while((temp=temp->n)){
      counter++;
   }
   v=((struct utils *)newint(counter,'+'));
   return v;
}

void
get(struct symbol * e,struct utils * v){
   struct list * temp = e->li;
   int counter = 1;
   int index = 0;
   int depth_list=((struct integer *)depth(e))->i;

   if(v->nodetype=='i'){
      index=((struct integer*)v)->i;
      if((index>depth_list)){
         printf("The index cannot be bigger than list depth\n");
         return;
      }
   }else{
      yyerror("The index must be an integer\n");
      return;
   }

   if(!temp && (e->value)){
      yyerror("The list does not exist\n");
      return;
   }

   if(!temp){
      printf("The list is empty\n");
      return;
   }

   do{
      if(counter==index){
         print_B(temp->s->value);
         break;
      }
      counter++;
   }while((temp=temp->n));
}

void
push(struct symbol * e,struct utils * v){
   struct list * temp = e->li;
   struct list * li=malloc(sizeof(struct list));

   if (!li) {
      yyerror("out of space");
      exit(0);
   }

   if(!temp && (e->value)){
      yyerror("the list does not exist");
      return;
   }

   if(!(temp)){
      li->s=setList(v);
      e->li=li;
   }else{
      while((temp->n)){
         temp=temp->n;
      }
      temp->n=li;
      li->s=setList(v);
      li->n=NULL;
   }
}

void
pop(struct symbol * e){
   struct list * temp = e->li;

   if(!temp && (e->value)){
      yyerror("The list does not exist\n");
      return;
   }

   if(!temp){
      printf("The list is empty\n");
      return;
   }

   if(!(temp->n)){
      printf("Removed element: ");
      print_B(e->li->s->value);
      free(e->li);
      e->li=NULL;
   }else{
      while((temp->n->n)){
         temp=temp->n;
      }
      printf("Removed element: ");
      print_B(temp->n->s->value);
      free(temp->n);
      temp->n=NULL;
   }
}

/* methods for images */
void
openImg(char * path){
   char * open = strdup("xdg-open ");     
   char * command; 

   command=strcat(open,path);
   system(command);
   printf("The image has been opened\n");
}

void
average(struct symref * v) {
   double mean;
   struct utils * temp1 = v -> s -> value;
   if (vips_avg((((struct img * ) temp1) -> img), & mean, NULL)) {
      vips_error_exit(NULL);
   }

   printf("mean pixel value = %g\n", mean);
}

void
invert(struct symref * l,struct ast * v) {
   VipsImage * out;
   char * path;
   struct utils * temp1 = l -> s -> value;
   if (vips_invert((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }
   path=getPath(v);

   /* If we wish to require user input from terminal, OLD
   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   */

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   openImg(path);
}

void
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
   path=getPath(r);

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   openImg(path);
}

void
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

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   openImg(path);
}

void
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

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   openImg(path);
}

void
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

   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
   openImg(path);
}

void
getWidth(struct symref * v) {
   struct utils * temp1 = v -> s -> value;
   printf("image width = %d\n", vips_image_get_width(((struct img * ) temp1) -> img));
}

void
getHeight(struct symref * v) {
   struct utils * temp1 = v -> s -> value;
   printf("image height = %d\n", vips_image_get_height(((struct img * ) temp1) -> img));
}

void
getBands(struct symref * v) {
   struct utils * temp1 = v -> s -> value;
   printf("number of bands = %d\n", vips_image_get_bands(((struct img * ) temp1) -> img));
}

void
print_B(struct utils * v) {
   struct utils * temp1;
   struct symbol * temp; 
   struct list * li;

   if(v -> nodetype == 'N' && ((struct symref * ) v) -> s->li) {
      temp=((struct symref * ) v) -> s;
      li=temp->li;
      do{
         print_B( ((struct utils *)li->s->value));
      } while((li=li->n));
   } else if(v -> nodetype == 'N' && !(((struct symref * ) v) -> s->li) && !(((struct symref * ) v) -> s->value)){
      printf("The list is empty\n");
   }else if (v -> nodetype == 'i') {
      printf("%d\n", ((struct integer * ) v) -> i);
   } else if (v -> nodetype == 'D') {
      printf("%f\n", ((struct doublePrecision * ) v) -> d);
   } else if (v -> nodetype == 'S') {
      printf("%s\n", strdup(((struct str * ) v) -> str));
   }else if (v -> nodetype == 'N') {
      temp1 = ((struct symref * ) v) -> s -> value;
      while (temp1->nodetype=='N') {
         temp1=((struct symref * ) temp1) -> s -> value;
      }
      if (temp1->nodetype == 'i') {
         printf("%i\n", ((struct integer * ) temp1) -> i);
      } else if(temp1->nodetype == 'D') {
         printf("%f\n", ((struct doublePrecision * ) temp1) -> d);
      } else if(temp1->nodetype == 'S') {
         printf("%s\n", ((struct str * ) temp1) -> str);
      } else if(temp1-> nodetype == 'P'){
         char * temp_path =strdup(((struct img *) temp1)->path);   
         openImg(temp_path);
      }
   } else if (v -> nodetype == 'M') {
      print_B(((struct ast *)v)->l);
   } else if(v-> nodetype == 'P'){
      printf("This element of the list is an image\n");
   } else {
      printf("%i\n",v->nodetype);
      printf("Node not found\n");
   }
}