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
         val=convert(((struct symref *)findNode(f, 1)), ((struct ast *)v)); //image
         return val;
      case b_average:
         val=average(((struct symref * ) v));
         return val;
      case b_min:
         val=min(((struct symref * ) v));
         return val;
      case b_max:
         val=max(((struct symref * ) v));
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
      case b_length:
         val= length( ((struct symref * ) v)->s );
         return val;
      case b_insert:
         insert(((struct symref *)findNode(f, 1))->s, ((struct utils *)findNode(f, 2)), v);
         return v;
      case b_remove:
         list_remove( ((struct symref *)findNode(f, 1))->s,v);
         return v;
      default:
         yyerror("Unknown built-in function %d", functype);
         return NULL;
      }
   }

/* methods for lists */
struct utils * 
length(struct symbol * e){
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
   int index;

   if( type(v)=='i' || (type(v)=='N' && type(getElement_sym(v))=='i') ){
      index=getElement_i(v);
      if( index>getElement_i(length(e))){
         printf("The index cannot be bigger than list length\n");
         return NULL;
      }else if(index<1){
         printf("The index cannot be less than 1\n");
         return NULL;
      }
   }else{
      yyerror("The index must be an integer\n");
      exit(0);
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
         return getElement_li(temp);
         break;
      }
      counter++;
   }while((temp=temp->n));
   return NULL;
}

void 
insert(struct symbol * e, struct utils * v, struct utils * s){
   struct list * temp = e->li;
   struct list * li=malloc(sizeof(struct list));
   int index;
   int counter=1;

   if (!li) {
      yyerror("out of space");
   }
   if(!temp && (e->value)){
      yyerror("the list does not exist");
   }
   if( type(s)=='i' || (type(s)=='N' && type(getElement_sym(s))=='i') ){
      index=getElement_i(s);
      if( index>getElement_i(length(e))){
         printf("The index cannot be bigger than list length\n");
         return;
      }else if(index<1){
         printf("The index cannot be less than 1\n");
         return;
      }
   }else{
      yyerror("The index must be an integer\n");
      exit(0);
   }

   if( index==(getElement_i(length(e))+1) ){
      push(e, v);
   }else{
      do{
         if(index==1){
            li->n=temp;
            li->s=setList(v);
            e->li=li;
            break;
         }else if(counter==(index-1)){
            li->n=temp->n;
            li->s=setList(v);
            temp->n=li;
            break;
         }
         counter++;
      }while((temp=temp->n));
   }
}

void 
list_remove(struct symbol * e, struct utils * v){
   struct list * temp = e->li;
   int index;
   int counter=1;

   if(!temp && (e->value)){
      yyerror("the list does not exist");
   }
   if( type(v)=='i' || (type(v)=='N' && type(getElement_sym(v))=='i') ){
      index=getElement_i(v);
      if( index>getElement_i(length(e))){
         printf("The index cannot be bigger than list length\n");
         return;
      }else if(index<1){
         printf("The index cannot be less than 1\n");
         return;
      }
   }else{
      yyerror("The index must be an integer\n");
      exit(0);
   }
   
   if( index==getElement_i(length(e)) ){
      pop(e);
   }else{
      do{
         if(index==1){
            e->li=temp->n;
            printf("Removed element: ");
            print_B(temp->s->value);
            break;
         }else if(counter==(index-1)){
            printf("Removed element: ");
            print_B(temp->n->s->value);
            temp->n=temp->n->n;
            break;
         }
         counter++;
      }while((temp=temp->n));
   }
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

   if(!v){
      yyerror("NULL pointer can't be printed!");
   }else if(isList(v)==1) {
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