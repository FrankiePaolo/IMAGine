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
      case b_zoom:
         val=zoom(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)),findNode(f, 3), ((struct ast *)v));
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
      case b_copyfile:
         val=copyfile(((struct symref *)findNode(f, 1)), ((struct ast *)v)); //image
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

   if(type(v)=='i'){
      index=getElement_i(v);
      if((index>depth_list)){
         printf("The index cannot be bigger than list depth\n");
         return NULL;
      }
      //((struct symref *)v)->s->value->nodetype=='i'
   }else if(type(v)=='N' && type(getElement_sym(v))=='i'){
      index=((struct integer *)((struct symref *)v)->s->value)->i;
      if((index>depth_list)){
         printf("The index cannot be bigger than list depth\n");
         return NULL;
      }
   }else{
      yyerror("The index must be an integer\n");
   }

   if(!temp && (e->value)){
      yyerror("The list does not exist\n");
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
   }

   if(!temp && (e->value)){
      yyerror("the list does not exist");
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
   }

   if(!temp){
      printf("The list is empty\n");
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
   struct list * li;

   if(isList(v)==1) {
      li=((struct symref * ) v)->s->li;
      do{
         print_B( getElement_li(li) );
      } while((li=li->n));
   } else if(isList(v)==0){
      printf("The list is empty\n");
   }else if (type(v) == 'i') {
      printf("%d\n", getElement_i(v));
   } else if (type(v) == 'D') {
      printf("%.6g\n", getElement_d(v));
   } else if (type(v) == 'S') {
      printf("%s\n", getElement_s(v));
   } else if (type(v) == 'N') {
      print_B( getElement_sym(v) );
   } else if(type(v) == 'P'){
      printf("This element is an image\n");
   } else {
      printf("%i\n",type(v));
      printf("Node not found\n");
   }
}