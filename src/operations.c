#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#  include <vips/vips.h>
#  include "utils.h"
#  include "builtin.h"

void
sum(struct utils * v, struct utils * l, struct utils * r) {

   if (type(l) == 'i' && type(r) == 'i') {
      putElement_i(v,getElement_i(l)+getElement_i(r));
   } else if (type(l) == 'D' && type(r) == 'D') {
      putElement_d(v,getElement_d(l)+getElement_d(r));
   } else if (type(l) == 'i' && type(r) == 'D') {
      putElement_d(v,getElement_i(l)+getElement_d(r));
   } else if (type(l) == 'D' && type(r) == 'i') {
      sum(v, r, l);
   } else if ((type(l) == 'S' && type(r) == 'i')) { 
      asprintf( &(((struct str *)v)->str), "%s%d", getElement_s(l), getElement_i(r) );
   } else if ((type(l) == 'i' && type(r) == 'S')) { 
      asprintf( &(((struct str *)v)->str), "%d%s", getElement_i(l), getElement_s(r) );
   } else if ((type(l) == 'S' && type(r) == 'D')) { 
      asprintf( &(((struct str *)v)->str), "%s%.6g", getElement_s(l), getElement_d(r) );
   } else if ((type(l) == 'D' && type(r) == 'S')) { 
      asprintf( &(((struct str *)v)->str), "%.6g%s", getElement_d(l), getElement_s(r) );
   } else if ((type(l) == 'S' && type(r) == 'S')) { 
      asprintf( &(((struct str *)v)->str), "%s%s", getElement_s(l), getElement_s(r) );
   } else if (type(l) == 'N' && type(r) != 'N') {
      sum(v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      sum(v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      sum(v, getElement_sym(l), getElement_sym(r));
   } else {
      yyerror("Cannot perform the sum operation on given values");
   }
}

void
subtract(struct utils * v, struct utils * l, struct utils * r) {

   if (type(l) == 'i' && type(r) == 'i') {
      putElement_i(v,getElement_i(l)-getElement_i(r));
   } else if (type(l) == 'D' && type(r) == 'D') {
      putElement_d(v,getElement_d(l)-getElement_d(r));
   } else if (type(l) == 'i' && type(r) == 'D') {
      putElement_d(v,getElement_i(l)-getElement_d(r));
   } else if (type(l) == 'D' && type(r) == 'i') {
      putElement_d(v,getElement_d(l)-getElement_i(r));
   } else if (type(l) == 'N' && type(r) != 'N') {
      subtract(v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      subtract(v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      subtract(v, getElement_sym(l), getElement_sym(r));
   } else {
      yyerror("Cannot perform the subtract operation on given values");
   }
}

void
multiply(struct utils * v, struct utils * l, struct utils * r) {

   if (type(l) == 'i' && type(r) == 'i') {
      putElement_i(v,getElement_i(l)*getElement_i(r));
   } else if (type(l) == 'D' && type(r) == 'D') {
      putElement_d(v,getElement_d(l)*getElement_d(r));
   } else if (type(l) == 'i' && type(r) == 'D') {
      putElement_d(v,getElement_i(l)*getElement_d(r));
   } else if (type(l) == 'D' && type(r) == 'i') {
      multiply(v, r, l);
   } else if ((type(l) == 'S' && type(r) == 'i')) {
      if(getElement_i(r) >0 ){
         asprintf( &(((struct str * ) v)->str), "%s", getElement_s(l));
         for(int i=0; i<getElement_i(r); i++){
            asprintf(&(((struct str * ) v)->str), "%s%s", getElement_s(v), getElement_s(l));
         }
      }else{
         yyerror("String multiply allowed only for positive integer");
      }       
   } else if ((type(l) == 'i' && type(r) == 'S')) {
      multiply(v, r , l); 
   } else if (type(l) == 'N' && type(r) != 'N') {
      multiply(v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      multiply(v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      multiply(v, getElement_sym(l), getElement_sym(r));
   } else {
      yyerror("Cannot perform the multipy operation on given values");
   }
}

struct utils *
divide(struct utils * l, struct utils * r) {
   struct utils * v;
   v=malloc(sizeof(struct doublePrecision));
   ((struct doublePrecision * ) v) -> nodetype = 'D';
   
   if (type(l) == 'i' && type(r) == 'D') {
      if(getElement_d(r) !=0){
         putElement_d(v,getElement_i(l) / getElement_d(r));
      }
   } else if (type(l) == 'D' && type(r) == 'i') {
      if(getElement_i(r) !=0){
         putElement_d(v,getElement_d(l) / getElement_i(r));
      }
   } else if (type(l) == 'i' && type(r) == 'i') {
      if(getElement_i(r) !=0){
         putElement_d(v,(double) (getElement_i(l)) / (double)(getElement_i(r)));
      }
   } else if (type(l) == 'D' && type(r) == 'D') {
      if(getElement_d(r) !=0){
         putElement_d(v,getElement_d(l) / getElement_d(r));
      }
   } else if (type(l) == 'N' && type(r) != 'N') {
      v=divide(getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      v=divide(l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      v=divide(getElement_sym(l), getElement_sym(r));
   } else {
      yyerror("Cannot perform the division operation on given values");
   }
   return v;
}

void
absoluteValue(struct utils * v, struct utils * l) {
   if (type(l) == 'N') {
      absoluteValue(v, getElement_sym(l));
   } else if (type(v) == 'i') {
      putElement_i(v,abs(getElement_i(l)));
   } else if (type(v) == 'D') {
      putElement_d(v,fabs(getElement_d(l)));
   } else {
      yyerror("Cannot perform the absolute value operation on given values");
   }
}

void
biggerThan(struct utils * v, struct utils * l, struct utils * r) {

   if (type(l) == 'N' && type(r) != 'N') {
      biggerThan( v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      biggerThan( v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      biggerThan( v, getElement_sym(l), getElement_sym(r));
   } else if (type(l) == 'i' && type(r) == 'D') {
      putElement_i(v,getElement_i(l) > getElement_d(r) ? 1 : 0);
   } else if (type(l) == 'D' && type(r) == 'i') {
      putElement_i(v,getElement_d(l) > getElement_i(r) ? 1 : 0);
   } else if (type(l) == 'i' && type(r) == 'i'){
      putElement_i(v,getElement_i(l) > getElement_i(r) ? 1 : 0);
   } else if(type(l) == 'D' && type(r) == 'D'){
      putElement_i(v,getElement_d(l) > getElement_d(r) ? 1 : 0);
   }else {
      yyerror("Cannot perform the comparison operation (>) on given values");
   }
}

void
smallerThan(struct utils * v, struct utils * l, struct utils * r) {

   if (type(l) == 'N' && type(r) != 'N') {
      smallerThan( v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      smallerThan( v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      smallerThan( v, getElement_sym(l), getElement_sym(r));
   }else if (type(l) == 'i' && type(r) == 'D') {
      putElement_i(v,getElement_i(l) < getElement_d(r) ? 1 : 0);
   }else if (type(l) == 'D' && type(r) == 'i') {
      putElement_i(v,getElement_d(l) < getElement_i(r) ? 1 : 0);
   }else if (type(l) == 'i' && type(r) == 'i'){
      putElement_i(v,getElement_i(l) < getElement_i(r) ? 1 : 0);
   }else if(type(l) == 'D' && type(r) == 'D'){
      putElement_i(v,getElement_d(l) < getElement_d(r) ? 1 : 0);
   }else {
      yyerror("Cannot perform the comparison operation (<) on given values");
   }
}

void
unequal(struct utils * v, struct utils * l, struct utils * r) {

   if (type(l) == 'i' && type(r) == 'D') {
      putElement_i(v,getElement_i(l) != getElement_d(r) ? 1 : 0);
   }else if (type(l) == 'D' && type(r) == 'i') {
      putElement_i(v,getElement_d(l) != getElement_i(r) ? 1 : 0);
   }else if (type(l) == 'i' && type(r) == 'i'){
      putElement_i(v,getElement_i(l) != getElement_i(r) ? 1 : 0);
   }else if(type(l) == 'D' && type(r) == 'D'){
      putElement_i(v,getElement_d(l) != getElement_d(r) ? 1 : 0);
   }else if (type(l) == 'S' && type(r) == 'S'){
      int temp;
      temp = strcmp(strdup(getElement_s(l)),strdup(getElement_s(r)));
      if(temp!=0){
         temp=1;
      }
      putElement_i(v,temp);
   }else if (type(l) == 'N' && type(r) != 'N') {
      unequal( v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      unequal( v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      unequal( v, getElement_sym(l), getElement_sym(r));
   }else {
      yyerror("Cannot perform the comparison operation (!=) on given values");
   }
}

void
equal(struct utils * v, struct utils * l, struct utils * r) {
   
   if (type(l) == 'i' && type(r) == 'D') {
      putElement_i(v,getElement_i(l) == getElement_d(r) ? 1 : 0);
   }else if (type(l) == 'D' && type(r) == 'i') {
      putElement_i(v,getElement_d(l) == getElement_i(r) ? 1 : 0);
   }else if (type(l) == 'i' && type(r) == 'i'){
      putElement_i(v,getElement_i(l) == getElement_i(r) ? 1 : 0);
   }else if(type(l) == 'D' && type(r) == 'D'){
      putElement_i(v,getElement_d(l) == getElement_d(r) ? 1 : 0);
   }else if (type(l) == 'S' && type(r) == 'S'){
      int temp;
      temp = strcmp(strdup(getElement_s(l)),strdup(getElement_s(r)));
      temp=getTruth(temp);
      putElement_i(v,temp);
   }else if (type(l) == 'N' && type(r) != 'N') {
      equal( v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      equal( v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      equal( v, getElement_sym(l), getElement_sym(r));
   }else {
      yyerror("Cannot perform the comparison operation (==) on given values");
   }
}

void
biggerOrEqual(struct utils * v, struct utils * l, struct utils * r) {
   
   if (type(l) == 'i' && type(r) == 'D') {
      putElement_i(v,getElement_i(l) >= getElement_d(r) ? 1 : 0);
   }else if (type(l) == 'D' && type(r) == 'i') {
      putElement_i(v,getElement_d(l) >= getElement_i(r) ? 1 : 0);
   }else if (type(l) == 'i' && type(r) == 'i'){
      putElement_i(v,getElement_i(l) >= getElement_i(r) ? 1 : 0);
   }else if(type(l) == 'D' && type(r) == 'D'){
      putElement_i(v,getElement_d(l) >= getElement_d(r) ? 1 : 0);
   }else if (type(l) == 'N' && type(r) != 'N') {
      biggerOrEqual( v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      biggerOrEqual( v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      biggerOrEqual( v, getElement_sym(l), getElement_sym(r));
   }else {
      yyerror("Cannot perform the comparison operation (>=) on given values");
   }
}

void
smallerOrEqual(struct utils * v, struct utils * l, struct utils * r) {
   
   if (type(l) == 'i' && type(r) == 'D') {
      putElement_i(v,getElement_i(l) <= getElement_d(r) ? 1 : 0);
   }else if (type(l) == 'D' && type(r) == 'i') {
      putElement_i(v,getElement_d(l) <= getElement_i(r) ? 1 : 0);
   }else if (type(l) == 'i' && type(r) == 'i'){
      putElement_i(v,getElement_i(l) <= getElement_i(r) ? 1 : 0);
   }else if(type(l) == 'D' && type(r) == 'D'){
      putElement_i(v,getElement_d(l) <= getElement_d(r) ? 1 : 0);
   }else if (type(l) == 'N' && type(r) != 'N') {
      smallerOrEqual( v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      smallerOrEqual( v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      smallerOrEqual( v, getElement_sym(l), getElement_sym(r));
   }else {
      yyerror("Cannot perform the comparison operation (<=) on given values");
   }
}