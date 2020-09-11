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
      unassignedError(v);

      switch (functype) {
      case b_print:
         print_B(v);
         return v;
      case b_width:
         imageError(v);
         val=getWidth(((struct symref * ) v)); //number
         return val;
      case b_height:
         imageError(v);
         val=getHeight(((struct symref * ) v)); //number
         return val;
      case b_bands:
         imageError(v);
         val=getBands(((struct symref * ) v)); //number
         return val;
      case b_crop:
         imageError(v);
         val=crop(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)), findNode(f, 3) , findNode(f, 4), findNode(f, 5) ,((struct ast *)v)); //image
         return val;
      case b_smartcrop:
         imageError(v);
         val=smartCrop(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)),findNode(f, 3), ((struct ast *)v));
         return val;
      case b_zoom:
         imageError(v);
         val=zoom(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)),findNode(f, 3), ((struct ast *)v));
         return val;
      case b_add:
         imageError(v);
         val=add( ((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)), ((struct ast *) v));
         return val;
      case b_subtract:
         imageError(v);
         val=subtract_img(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)), ((struct ast *)v));
         return val;
      case b_convert:
         imageError(v);
         val=toColorSpace(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v));
         return val;
      case b_invert:
         imageError(v);
         val=invert(((struct symref *)findNode(f, 1)), ((struct ast *)v)); //image
         return val;
      case b_copyfile:
         imageError(v);
         val=convert(((struct symref *)findNode(f, 1)), ((struct ast *)v)); //image
         return val;
      case b_average:
         imageError(v);
         val=average(((struct symref * ) v));
         return val;
      case b_min:
         imageError(v);
         val=min(((struct symref * ) v));
         return val;
      case b_max:
         imageError(v);
         val=max(((struct symref * ) v));
         return val;
      case b_flip:
         imageError(v);
         val=flip(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v)); //image
         return val;
      case b_rotate:
         imageError(v);
         val=rotate(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v)); //image
         return val;
      case b_norm:
         imageError(v);
         val=norm((struct symref *)findNode(f, 1),((struct ast *)v));
         return val;
      case b_histeq:
         imageError(v);
         val=histeq((struct symref *)findNode(f, 1),((struct ast *)v));
         return val;
      case b_gaussianblur:
         imageError(v);
         val=gaussianBlur(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v));
         return val;
      case b_canny:
         imageError(v);
         val=canny(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_sobel:
         imageError(v);
         val=sobel(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_sharpen:
         imageError(v);
         val=sharpen(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_get:
         val=get( ((struct symref *)findNode(f, 1)),v);
         return val;
      case b_push:
         push( ((struct symref *)findNode(f, 1)),v);
         return v;
      case b_pop:
         pop( ((struct symref * ) v) );
         return v;
      case b_length:
         val= length( ((struct symref * ) v) );
         return val;
      case b_insert:
         insert(((struct symref *)findNode(f, 1)), ((struct utils *)findNode(f, 2)), v);
         return v;
      case b_remove:
         list_remove( ((struct symref *)findNode(f, 1)),v);
         return v;
      default:
         yyerror("Unknown built-in function %d", functype);
         return NULL;
      }
   }

/* methods for lists */
struct utils * 
length(struct symref * e){
   struct utils * v;
   struct list * temp = e->s->li;
   int counter=1;

   if(listCheck(e)==-1){
      yyerror("The list does not exist!");
      exit(0);
   }

   if(listCheck(e)==0){
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
get(struct symref * e,struct utils * v){
   struct list * temp = e->s->li;
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

   if(listCheck(e)==-1){
      yyerror("The list does not exist!");
      exit(0);
   }

   if(listCheck(e)==0){
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
insert(struct symref * e, struct utils * v, struct utils * s){
   struct list * temp = e->s->li;
   struct list * li=malloc(sizeof(struct list));
   int index;
   int counter=1;

   if (!li) {
      yyerror("out of space");
      exit(0);
   }
   if(listCheck(e)==-1){
      yyerror("The list does not exist!");
      exit(0);
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
            e->s->li=li;
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
list_remove(struct symref * e, struct utils * v){
   struct list * temp = e->s->li;
   int index;
   int counter=1;

   if(listCheck(e)==-1){
      yyerror("The list does not exist!");
      exit(0);
   }
   if( type(v)=='i' || (type(v)=='N' && type(getElement_sym(v))=='i') ){
      index=getElement_i(v);
      if( index>getElement_i(length(e))){
         printf("The index cannot be bigger than list length\n");
         return;
      }else if(index<1){
         printf("The index cannot be less than 1!\n");
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
            e->s->li=temp->n;
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
push(struct symref * e,struct utils * v){
   struct list * temp = e->s->li;
   struct list * li=malloc(sizeof(struct list));

   if (!li) {
      yyerror("Out of space");
      exit(0);
   }

   if(listCheck(e)==-1){
      yyerror("The list does not exist!");
      exit(0);
   }

   if(!(temp)){
      li->s=setList(v);
      e->s->li=li;
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
pop(struct symref * e){
   struct list * temp = e->s->li;

   if(listCheck(e)==-1){
      yyerror("The list does not exist!");
      exit(0);
   }

   if(listCheck(e)==0){
      printf("The list is empty\n");
      return;
   }

   if(!(temp->n)){
      printf("Removed element: ");
      print_B(e->s->li->s->value);
      free(e->s->li);
      e->s->li=NULL;
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
      exit(0);
   }else if (type(v) == 'i') {
      printf("%d\n", getElement_i(v));
   } else if (type(v) == 'D') {
      printf("%.6g\n", getElement_d(v));
   } else if (type(v) == 'S') {
      printf("%s\n", getElement_s(v));
   } else if(type(v) == 'U'){
      printf("This variable is not allocated!\n");
   } else if(type(v) == 'P'){
      printf("This element is an image\n");
   } else if(listCheck( ((struct symref * )v))==1) {
      li=((struct symref * ) v)->s->li;
      do{
         print_B( getElement_li(li) );
      } while((li=li->n));
   } else if(listCheck(((struct symref * )v))==0){
      printf("The list is empty\n");
   } else if (type(v) == 'N') {
      print_B( getElement_sym(v) );
   } else {
      printf("Node not found: %i\n",type(v));
   }
}