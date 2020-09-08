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
   char temp[50];

   if (type(l) == 'i' && r == NULL) {
      putElement_i(v,getElement_i(l));
   } else if (type(l) == 'D' && r == NULL) {
      putElement_d(v,getElement_d(l));
   } else if (type(l) == 'i' && type(r) == 'D') {
      putElement_d(v,getElement_i(l)+getElement_d(r));
   } else if (type(l) == 'D' && type(r) == 'i') {
      sum(v, r, l);
   } else if (type(l) == 'i' && type(r) == 'i') {
      putElement_i(v,getElement_i(l)+getElement_i(r));
   } else if (type(l) == 'D' && type(r) == 'D') {
      putElement_d(v,getElement_d(l)+getElement_d(r));
   } else if ((type(l) == 'S' && type(r) == 'i')) { 
      sprintf(temp, "%d", getElement_i(r));
      strcat( getElement_s(l), strdup(temp) );
      putElement_s(v,getElement_s(l));
   } else if ((type(l) == 'i' && type(r) == 'S')) { 
      sprintf(temp, "%d", getElement_i(l));
      strcat( temp, getElement_s(r) );
      putElement_s(v,temp);
   } else if ((type(l) == 'S' && type(r) == 'D')) { 
      sprintf(temp, "%.6g", getElement_d(r));
      strcat( getElement_s(l), strdup(temp) );
      putElement_s(v,getElement_s(l));
   } else if ((type(l) == 'D' && type(r) == 'S')) { 
      sprintf(temp, "%.6g", getElement_d(l));
      strcat( temp, getElement_s(r) );
      putElement_s(v,temp);
   } else if ((type(l) == 'S' && type(r) == 'S')) { 
      strcat(getElement_s(l),getElement_s(r));
      putElement_s(v,getElement_s(l));
   } else if (type(l) == 'N' && type(r) != 'N') {
      sum(v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      sum(v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      sum(v, getElement_sym(l), getElement_sym(r));
   } else {
      yyerror("Unexpected type, %c %c", type(l), type(r));
   }
}

void
subtract(struct utils * v, struct utils * l, struct utils * r) {

   if (type(l) == 'i' && r == NULL) {
      putElement_i(v,getElement_i(l));
   } else if (type(l) == 'D' && r == NULL) {
      putElement_d(v,getElement_d(l));
   } else if (type(l) == 'i' && type(r) == 'D') {
      putElement_d(v,getElement_i(l) - getElement_d(r));
   } else if (type(l) == 'D' && type(r) == 'i') {
       putElement_d(v,getElement_d(l)-getElement_i(r));
   } else if (type(l) == 'i' && type(r) == 'i') {
      putElement_i(v,getElement_i(l)-getElement_i(r));
   } else if (type(l) == 'D' && type(r) == 'D') {
      putElement_d(v,getElement_d(l)-getElement_d(r));
   } else if (type(l) == 'N' && type(r) != 'N') {
      subtract(v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      subtract(v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      subtract(v, getElement_sym(l), getElement_sym(r));
   } else {
      yyerror("Unexpected type, %c %c", type(l), type(r));
   }
}

void
multiply(struct utils * v, struct utils * l, struct utils * r) {

   if (type(l) == 'i' && r == NULL) {
      putElement_i(v,getElement_i(l));
   } else if (type(l) == 'D' && r == NULL) {
      putElement_d(v,getElement_d(l));
   } else if (type(l) == 'i' && type(r) == 'D') {
      putElement_d(v,getElement_i(l)*getElement_d(r));
   } else if (type(l) == 'D' && type(r) == 'i') {
      multiply(v, r, l);
   } else if (type(l) == 'i' && type(r) == 'i') {
      putElement_i(v,getElement_i(l) * getElement_i(r));
   } else if (type(l) == 'D' && type(r) == 'D') {
      putElement_d(v,getElement_d(l)*getElement_d(r));
   } else if ((type(l) == 'S' && type(r) == 'i')) {
      if(getElement_i(r) >0 ){
         asprintf( &(((struct str * ) v)->str), "%s", getElement_s(l));
         for(int i=0; i<getElement_i(r); i++){
            asprintf(&(((struct str * ) v)->str), "%s%s", getElement_s(v), getElement_s(l));
         }
      }else{
         yyerror("String multiply allowed only for positive integer\n");
      }       
   } else if ((type(l) == 'i' && type(r) == 'S')) { 
      if(getElement_i(l) >0 ){
         asprintf( &(((struct str * ) v)->str), "%s", getElement_s(r));
         for(int i=0; i<getElement_i(l); i++){
            asprintf(&(((struct str * ) v)->str), "%s%s", getElement_s(v), getElement_s(r));
         }
      }else{
         yyerror("String multiply allowed only for positive integer\n");
      }  
   } else if (type(l) == 'N' && type(r) != 'N') {
      multiply(v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      multiply(v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      multiply(v, getElement_sym(l), getElement_sym(r));
   } else {
      yyerror("Unexpected type, %c %c", type(l), type(r));
   }
}

struct utils *
divide(struct utils * l, struct utils * r) {
   struct utils * v;
   v=malloc(sizeof(struct doublePrecision));
   ((struct doublePrecision * ) v) -> nodetype = 'D';
   
   if (type(l) == 'i' && type(r) == 'D') {
      if(((struct doublePrecision * ) r) -> d !=0){
         ((struct doublePrecision *)v) -> d = getElement_i(l) / ((struct doublePrecision * ) r) -> d;
      }
   } else if (type(l) == 'D' && type(r) == 'i') {
      if(((struct integer * ) r) -> i !=0){
         ((struct doublePrecision *)v) -> d = ((struct doublePrecision * ) l) -> d / ((struct integer * ) r) -> i;
      }
   } else if (type(l) == 'i' && type(r) == 'i') {
      if(((struct integer * ) r) -> i !=0){
         ((struct doublePrecision *)v) -> d = (double) (getElement_i(l)) / (double)(((struct integer * ) r) -> i);
      }
   } else if (type(l) == 'D' && type(r) == 'D') {
      if(((struct doublePrecision * ) r) -> d !=0){
         ((struct doublePrecision *)v) -> d = ((struct doublePrecision * ) l) -> d / ((struct doublePrecision * ) r) -> d;
      }
   } else if (type(l) == 'N' && type(r) != 'N') {
      v=divide(getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      v=divide(l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      v=divide(getElement_sym(l), getElement_sym(r));
   } else {
      yyerror("Unexpected type, %c %c", type(l), type(r));
   }
   return v;
}

void
absoluteValue(struct utils * v, struct utils * l) {
   if (type(l) == 'N') {
      absoluteValue(v, getElement_sym(l));
   } else if (type(v) == 'i') {
      ((struct integer * ) v) -> i = abs(getElement_i(l));
   } else if (type(v) == 'D') {
      ((struct doublePrecision * ) v) -> d = fabs(((struct doublePrecision * ) l) -> d);
   } else {
      yyerror("Unexpected type, %c %c", type(l));
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
   } else if (type(l) == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = getElement_i(l) > ((struct doublePrecision * ) r) -> d ? 1 : 0;
   } else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d > ((struct integer * ) r) -> i ? 1 : 0;
   } else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = getElement_i(l) > ((struct integer * ) r) -> i ? 1 : 0;
   } else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d > ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else {
      yyerror("Unexpected type, %c %c", type(l), type(r));
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
   }else if (type(l) == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = getElement_i(l) < ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d < ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = getElement_i(l) < ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d < ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else {
      yyerror("Unexpected type, %c %c", type(l), type(r));
   }
}

void
unequal(struct utils * v, struct utils * l, struct utils * r) {

   if (type(l) == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = getElement_i(l) != ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d != ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = getElement_i(l) != ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d != ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (type(l) == 'S' && r->nodetype == 'S'){
      int temp;
      temp = strcmp(strdup(((struct str *)l)->str),strdup(((struct str *)r)->str));
      if(temp!=0){
         temp=1;
      }
      ((struct integer * ) v) -> i = temp;
   }else if (type(l) == 'N' && type(r) != 'N') {
      unequal( v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      unequal( v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      unequal( v, getElement_sym(l), getElement_sym(r));
   }else {
      yyerror("Unexpected type, %c %c", type(l), type(r));
   }
}

void
equal(struct utils * v, struct utils * l, struct utils * r) {
   
   if (type(l) == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = getElement_i(l) == ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d == ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = getElement_i(l) == ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d == ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (type(l) == 'S' && r->nodetype == 'S'){
      int temp;
      temp = strcmp(strdup(((struct str *)l)->str),strdup(((struct str *)r)->str));
      temp=getTruth(temp);
      ((struct integer * ) v) -> i = temp;
   }else if (type(l) == 'N' && type(r) != 'N') {
      equal( v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      equal( v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      equal( v, getElement_sym(l), getElement_sym(r));
   }else {
      yyerror("Unexpected type, %c %c", type(l), type(r));
   }
}

void
biggerOrEqual(struct utils * v, struct utils * l, struct utils * r) {
   
   if (type(l) == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = getElement_i(l) >= ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d >= ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = getElement_i(l) >= ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d >= ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (type(l) == 'N' && type(r) != 'N') {
      biggerOrEqual( v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      biggerOrEqual( v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      biggerOrEqual( v, getElement_sym(l), getElement_sym(r));
   }else {
      yyerror("Unexpected type, %c %c", type(l), type(r));
   }
}

void
smallerOrEqual(struct utils * v, struct utils * l, struct utils * r) {
   
   if (type(l) == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = getElement_i(l) <= ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d <= ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = getElement_i(l) <= ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d <= ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (type(l) == 'N' && type(r) != 'N') {
      smallerOrEqual( v, getElement_sym(l), r);
   } else if (type(l) != 'N' && type(r) == 'N') {
      smallerOrEqual( v, l, getElement_sym(r));
   } else if (type(l) == 'N' && type(r) == 'N') {
      smallerOrEqual( v, getElement_sym(l), getElement_sym(r));
   }else {
      yyerror("Unexpected type, %c %c", type(l), type(r));
   }
}