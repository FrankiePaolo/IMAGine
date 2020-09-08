#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#  include <vips/vips.h>
#  include "utils.h"
#  include "builtin.h"
#  include "imageops.h"
#  include "eval.h"

struct utils *
   callbuiltin(struct fncall * f) {
      enum bifs functype = f -> functype;
      struct utils * v = eval(f -> l);  
      struct utils * val;
      // Find tree node

      switch (functype) {
      case b_print:
         print_B(v);
         return v;
      case b_width:
         val=getWidth(((struct symref * ) v)); //number
         return val;
      case b_height:
         val=getHeight(((struct symref * ) v)); //number
         return val;
      case b_bands:
         val=getBands(((struct symref * ) v)); //number
         return val;
      case b_crop:
         val=crop(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)), findNode(f, 3) , findNode(f, 4), findNode(f, 5) ,((struct ast *)v)); //image
         return val;
      case b_smartcrop:
         val=smartCrop(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)),findNode(f, 3), ((struct ast *)v));
         return val;
      case b_add:
         val=add( ((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)), ((struct ast *) v));
         return val;
      case b_subtract:
         val=subtract_img(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)), ((struct ast *)v));
         return val;
      case b_convert:
         val=toColorSpace(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v));
         return val;
      case b_invert:
         val=invert(((struct symref *)findNode(f, 1)), ((struct ast *)v)); //image
         return val;
      case b_average:
         val=average(((struct symref * ) v));
         return val;
      case b_flip:
         val=flip(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v)); //image
         return val;
      case b_rotate:
         val=rotate(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v)); //image
         return val;
      case b_norm:
         val=norm((struct symref *)findNode(f, 1),((struct ast *)v));
         return val;
      case b_histeq:
         val=histeq((struct symref *)findNode(f, 1),((struct ast *)v));
         return val;
      case b_gaussianblur:
         val=gaussianBlur(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v));
         return val;
      case b_canny:
         val=canny(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_sobel:
         val=sobel(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_sharpen:
         val=sharpen(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_get:
         val=get( ((struct symref *)findNode(f, 1))->s,v);
         return val;
      case b_push:
         push( ((struct symref *)findNode(f, 1))->s,v);
         return v;
      case b_pop:
         pop( ((struct symref * ) v)->s );
         return v;
      case b_depth:
         val= depth( ((struct symref * ) v)->s );
         return val;
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

struct utils *
get(struct symbol * e,struct utils * v){
   struct list * temp = e->li;
   int counter = 1;
   int index = 0;
   int depth_list=((struct integer *)depth(e))->i;

   if(v->nodetype=='i'){
      index=((struct integer*)v)->i;
      if((index>depth_list)){
         printf("The index cannot be bigger than list depth\n");
         return NULL;
      }
   }else if(v->nodetype=='N' && ((struct symref *)v)->s->value->nodetype=='i'){ 
      index=((struct integer *)((struct symref *)v)->s->value)->i;
      if((index>depth_list)){
         printf("The index cannot be bigger than list depth\n");
         return NULL;
      }
   }else{
      yyerror("The index must be an integer\n");
      return NULL;
   }

   if(!temp && (e->value)){
      yyerror("The list does not exist\n");
      return NULL;
   }

   if(!temp){
      printf("The list is empty\n");
      return NULL;
   }

   do{
      if(counter==index){
         return(temp->s->value);
         break;
      }
      counter++;
   }while((temp=temp->n));
   return NULL;
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
      printf("%.6g\n", ((struct doublePrecision * ) v) -> d);
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
         //char * temp_path =strdup(((struct img *) temp1)->path); 
         //openImg(temp_path);
         printf("This is an image\n");
      }
   } else if (v -> nodetype == 'M') {
      print_B( ((struct utils *)((struct ast *)v)->l) );
   } else if(v-> nodetype == 'P'){
      printf("This element of the list is an image\n");
   } else {
      printf("%i\n",v->nodetype);
      printf("Node not found\n");
   }
}