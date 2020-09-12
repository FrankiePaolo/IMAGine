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
      unassignedError(v);

      switch (functype) {
      case b_print:
         argumentsCheck(f, 1);
         print_B(v);
         return v;
      case b_width:
         argumentsCheck(f, 1);
         imageError( ((struct ast *)v) );
         val=getWidth(((struct symref * ) v));
         return val;
      case b_height:
         argumentsCheck(f, 1);
         imageError(((struct ast *)v));
         val=getHeight(((struct symref * ) v));
         return val;
      case b_bands:
         argumentsCheck(f, 1);
         imageError(((struct ast *)v));
         val=getBands(((struct symref * ) v));
         return val;
      case b_average:
         argumentsCheck(f, 1);
         imageError(((struct ast *)v));
         val=average(((struct symref * ) v));
         return val;
      case b_min:
         argumentsCheck(f, 1);
         imageError(((struct ast *)v));
         val=min(((struct symref * ) v));
         return val;
      case b_max:
         argumentsCheck(f, 1);
         imageError(((struct ast *)v));
         val=max(((struct symref * ) v));
         return val;
      case b_invert:
         argumentsCheck(f, 2);
         imageError(findNode(f, 1));
         val=invert(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_histeq:
         argumentsCheck(f, 2);
         imageError(findNode(f, 1));
         val=histeq((struct symref *)findNode(f, 1),((struct ast *)v));
         return val;
      case b_norm:
         argumentsCheck(f, 2);
         imageError(findNode(f, 1));
         val=norm((struct symref *)findNode(f, 1),((struct ast *)v));
         return val;
      case b_canny:
         argumentsCheck(f, 2);
         imageError(findNode(f, 1));
         val=canny(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_sobel:
         argumentsCheck(f, 2);
         imageError(findNode(f, 1));
         val=sobel(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_sharpen:
         argumentsCheck(f, 2);
         imageError(findNode(f, 1));
         val=sharpen(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_copyfile:
         argumentsCheck(f, 2);
         imageError(findNode(f, 1));
         val=convert(((struct symref *)findNode(f, 1)), ((struct ast *)v));
         return val;
      case b_convert:
         argumentsCheck(f, 3);
         imageError(findNode(f, 1));
         val=toColorSpace(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v));
         return val;
      case b_add:
         argumentsCheck(f, 3);
         imageError(findNode(f, 1));
         imageError(findNode(f, 2));
         val=add( ((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)), ((struct ast *) v));
         return val;
      case b_subtract:
         argumentsCheck(f, 3);
         imageError(findNode(f, 1));
         imageError(findNode(f, 2));
         val=subtract_img(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)), ((struct ast *)v));
         return val;
      case b_rotate:
         argumentsCheck(f, 3);
         imageError(findNode(f, 1));
         val=rotate(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v));
         return val;
      case b_flip:
         argumentsCheck(f, 3);
         imageError(findNode(f, 1));
         val=flip(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v)); 
         return val;
      case b_gaussianblur:
         argumentsCheck(f, 3);
         imageError(findNode(f, 1));
         val=gaussianBlur(((struct symref *)findNode(f, 1)), findNode(f, 2), ((struct ast *)v));
         return val;
      case b_smartcrop:
         argumentsCheck(f, 4);
         imageError(findNode(f, 1));
         val=smartCrop(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)),findNode(f, 3), ((struct ast *)v));
         return val;
      case b_zoom:
         argumentsCheck(f, 4);
         imageError(findNode(f, 1));
         val=zoom(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)),findNode(f, 3), ((struct ast *)v));
         return val;
      case b_crop:
         argumentsCheck(f, 6);
         imageError(findNode(f, 1));
         val=crop(((struct symref *)findNode(f, 1)), ((struct symref *)findNode(f, 2)), findNode(f, 3) , findNode(f, 4), findNode(f, 5) ,((struct ast *)v));
         return val;
      case b_get:
         argumentsCheck(f, 2);
         listError(findNode(f, 1));
         val=get( ((struct symref *)findNode(f, 1)),v);
         return val;
      case b_push:
         argumentsCheck(f, 2);
         listError(findNode(f, 1));
         push(((struct symref *)findNode(f, 1)),v);
         return v;
      case b_pop:
         argumentsCheck(f, 1);
         listError(((struct ast *)v));
         pop( ((struct symref * ) v) );
         return v;
      case b_length:
         argumentsCheck(f, 1);
         listError(((struct ast *)v));
         //imageError( ((struct ast *)v) );
         val= length( ((struct symref * ) v) );
         return val;
      case b_insert:
         argumentsCheck(f, 3);
         listError(findNode(f, 1));
         insert(((struct symref *)findNode(f, 1)), ((struct utils *)findNode(f, 2)), v);
         return v;
      case b_remove:
         argumentsCheck(f, 2);
         listError(findNode(f, 1));
         list_remove( ((struct symref *)findNode(f, 1)),v);
         return v;
      case b_show:
         argumentsCheck(f, 1);
         imageError( ((struct ast *)v) );
         showImg(((struct symref * ) v));
         return v;
      default:
         yyerror("Unknown built-in function %d", functype);
         return NULL;
      }
   }

/* Returns the number of elements in the list */
struct utils * 
length(struct symref * e){
   struct utils * v;
   struct list * temp = e->s->li;
   int counter=1;

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

/* Appends the element to the list */
void
push(struct symref * e,struct utils * v){
   struct list * temp = e->s->li;
   struct list * li=malloc(sizeof(struct list));

   if (!li) {
      yyerror("Out of space");
      exit(0);
   }
   if(listCheck((struct symref *)v)!=-1 && strcmp(e->s->name, ((struct symref *)v)->s->name)==0){
      yyerror("Can't insert the same list!");
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

/* Inserts element in the given position */
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
   if( type(s)=='i' || (type(s)=='N' && type(getElement_sym(s))=='i') ){
      index=getElement_i(s);
      if( index>(getElement_i(length(e))+1)){
         printf("The index cannot be bigger than list length\n");
         return;
      }else if(index<1){
         printf("The index cannot be less than 1\n");
		   exit(0);
      }
   }else{
      yyerror("The index must be an integer\n");
      exit(0);
   }
   if(listCheck((struct symref *)v)!=-1 && strcmp(e->s->name, ((struct symref *)v)->s->name)==0){
      yyerror("Can't insert the same list!");
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

/* Removes element from the given position */
void 
list_remove(struct symref * e, struct utils * v){
   struct list * temp = e->s->li;
   int index;
   int counter=1;

   if( type(v)=='i' || (type(v)=='N' && type(getElement_sym(v))=='i') ){
      index=getElement_i(v);
      if( index>getElement_i(length(e))){
         printf("The index cannot be bigger than list length\n");
         return;
      }else if(index<1){
         printf("The index cannot be less than 1!\n");
		   exit(0);
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

            if(type(temp->s->value)=='l'){
               printf("%s. This is a list.\n", temp->s->name);
            }else{
               print_B(temp->s->value);
            }
            break;
         }else if(counter==(index-1)){
            printf("Removed element: ");

            if(type(temp->n->s->value)=='l'){
               printf("%s. This is a list.\n", temp->n->s->name);
            }else{
               print_B(temp->n->s->value);
            }
            temp->n=temp->n->n;
            break;
         }
         counter++;
      }while((temp=temp->n));
   }
}

/* Removes and returns the last element */
void
pop(struct symref * e){
   struct list * temp=e->s->li;

   if(listCheck(e)==0){
      printf("The list is empty\n");
      return;
   }

   if(!(temp->n)){
      printf("Removed element: ");
      if(type(temp->n->s->value)=='l'){
         printf("%s. This is a list\n", temp->n->s->name);
      }else{
         print_B(e->s->li->s->value);
      }
      free(e->s->li);
      e->s->li=NULL;
   }else{
      while((temp->n->n)){
         temp=temp->n;
      }
      printf("Removed element: ");
      if(type(temp->n->s->value)=='l'){
         printf("%s. This is a list\n", temp->n->s->name);
      }else{
         print_B(temp->n->s->value);
      }
      free(temp->n);
      temp->n=NULL;
   }
}

/* Returns the element in the given position */ 
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
         yyerror("The index cannot be less than 1\n");
		   exit(0);
      }
   }else{
      yyerror("The index must be an integer\n");
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

/* Prints the elements provided */
void
print_B(struct utils * v) {
   struct list * li;

   if(!v){
      yyerror("NULL pointer can't be printed!");
      exit(0);
   } else if (type(v) == 'i') {
      printf("%d\n", getElement_i(v));
   } else if (type(v) == 'D') {
      printf("%.6g\n", getElement_d(v));
   } else if (type(v) == 'S') {
      printf("%s\n", getElement_s(v));
   } else if(type(v) == 'U'){
      printf("This variable is not allocated!\n");
   } else if(type(v) == 'P'){
      printf("This element is an image\n");
   } else if(listCheck(((struct symref * )v))==1) {
      li=((struct symref * ) v)->s->li;
      do{
         if(type(getElement_li(li))!='l'){
            print_B( getElement_li(li));
         }else{
            print_B((struct utils *) li->s->li);
         }
      } while((li=li->n));
   } else if(listCheck(((struct symref * )v))==0){
      printf("The list is empty\n");
   } else if (type(v) == 'N') {
      print_B( getElement_sym(v) );
   } else if (type(v) == 'l') {
      li=(struct list *) v;
      do{
         if(type(getElement_li(li))!='l'){
            print_B( getElement_li(li));
         }else{
            print_B((struct utils *) li->s->li);
         }
      } while((li=li->n));
   } else {
      yyerror("Node not found in function print: %i", type(v));
      exit(0);
   }
}