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
   struct utils * tempName, * tempName2;
   char temp[50];

   if (l -> nodetype == 'i' && r == NULL) {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i;
   } else if (l -> nodetype == 'D' && r == NULL) {
      ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d;
   } else if (l -> nodetype == 'i' && r -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = ((struct integer * ) l) -> i + ((struct doublePrecision * ) r) -> d;
   } else if (l -> nodetype == 'D' && r -> nodetype == 'i') {
      ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d + ((struct integer * ) r) -> i;
   } else if (l -> nodetype == 'i' && r -> nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i + ((struct integer * ) r) -> i;
   } else if (l -> nodetype == 'D' && r -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d + ((struct doublePrecision * ) r) -> d;
   } else if ((l -> nodetype == 'S' && r -> nodetype == 'i')) { 
      sprintf(temp, "%d", ((struct integer * ) r) -> i);
      ((struct str * ) v)->str = strcat( strdup( ((struct str * ) l) -> str), temp );
   }else if ((l -> nodetype == 'i' && r -> nodetype == 'N')) {
      if (((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i + ((struct integer * ) tempName) -> i;
      } else if (((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct integer * ) l) -> i + ((struct doublePrecision * ) tempName) -> d;
      }
   } else if ((l -> nodetype == 'D' && r -> nodetype == 'N')) {
      if (((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d + ((struct integer * ) tempName) -> i;
      } else if (((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d + ((struct doublePrecision * ) tempName) -> d;
      }
   } else if (l -> nodetype == 'N' && r -> nodetype == 'i') {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i + ((struct integer * ) r) -> i;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d + ((struct integer * ) r) -> i;
      }
   } else if ((l -> nodetype == 'N' && r -> nodetype == 'D')) {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct integer * ) tempName) -> i + ((struct doublePrecision * ) r) -> d;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d + ((struct doublePrecision * ) r) -> d;
      }
   } else if ((l -> nodetype == 'N' && r -> nodetype == 'N')) {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i' && ((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i + ((struct integer * ) tempName2) -> i;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'i' && ((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct integer * ) tempName) -> i + ((struct doublePrecision * ) tempName2) -> d;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D' && ((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d + ((struct integer * ) tempName2) -> i;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D' && ((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d + ((struct doublePrecision * ) tempName2) -> d;
      }
   } else {
      yyerror("Unexpected type, %c %c", l -> nodetype, r -> nodetype);
   }
}

void
subtract(struct utils * v, struct utils * l, struct utils * r) {
   struct utils * tempName, * tempName2;

   if (l -> nodetype == 'i' && r == NULL) {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i;
   } else if (l -> nodetype == 'D' && r == NULL) {
      ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d;
   } else if (l -> nodetype == 'i' && r -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = ((struct integer * ) l) -> i - ((struct doublePrecision * ) r) -> d;
   } else if (l -> nodetype == 'D' && r -> nodetype == 'i') {
      ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d - ((struct integer * ) r) -> i;
   } else if (l -> nodetype == 'i' && r -> nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i - ((struct integer * ) r) -> i;
   } else if (l -> nodetype == 'D' && r -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d - ((struct doublePrecision * ) r) -> d;
   } else if ((l -> nodetype == 'i' && r -> nodetype == 'N')) {
      if (((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i - ((struct integer * ) tempName) -> i;
      } else if (((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct integer * ) l) -> i - ((struct doublePrecision * ) tempName) -> d;
      }
   } else if ((l -> nodetype == 'D' && r -> nodetype == 'N')) {
      if (((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d - ((struct integer * ) tempName) -> i;
      } else if (((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d - ((struct doublePrecision * ) tempName) -> d;
      }
   } else if (l -> nodetype == 'N' && r -> nodetype == 'i') {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i - ((struct integer * ) r) -> i;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d - ((struct integer * ) r) -> i;
      }
   } else if ((l -> nodetype == 'N' && r -> nodetype == 'D')) {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct integer * ) tempName) -> i - ((struct doublePrecision * ) r) -> d;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d - ((struct doublePrecision * ) r) -> d;
      }
   } else if ((l -> nodetype == 'N' && r -> nodetype == 'N')) {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i' && ((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i - ((struct integer * ) tempName2) -> i;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'i' && ((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct integer * ) tempName) -> i - ((struct doublePrecision * ) tempName2) -> d;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D' && ((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d - ((struct integer * ) tempName2) -> i;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D' && ((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d - ((struct doublePrecision * ) tempName2) -> d;
      }
   } else {
      yyerror("Unexpected type, %c %c", l -> nodetype, r -> nodetype);
   }
}

void
multiply(struct utils * v, struct utils * l, struct utils * r) {
   struct utils * tempName, * tempName2;

   if (l -> nodetype == 'i' && r == NULL) {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i;
   } else if (l -> nodetype == 'D' && r == NULL) {
      ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d;
   } else if (l -> nodetype == 'i' && r -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = ((struct integer * ) l) -> i * ((struct doublePrecision * ) r) -> d;
   } else if (l -> nodetype == 'D' && r -> nodetype == 'i') {
      ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d * ((struct integer * ) r) -> i;
   } else if (l -> nodetype == 'i' && r -> nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i * ((struct integer * ) r) -> i;
   } else if (l -> nodetype == 'D' && r -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d * ((struct doublePrecision * ) r) -> d;
   } else if ((l -> nodetype == 'i' && r -> nodetype == 'N')) {
      if (((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i * ((struct integer * ) tempName) -> i;
      } else if (((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct integer * ) l) -> i * ((struct doublePrecision * ) tempName) -> d;
      }
   } else if ((l -> nodetype == 'D' && r -> nodetype == 'N')) {
      if (((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d * ((struct integer * ) tempName) -> i;
      } else if (((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d * ((struct doublePrecision * ) tempName) -> d;
      }
   } else if (l -> nodetype == 'N' && r -> nodetype == 'i') {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i * ((struct integer * ) r) -> i;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d * ((struct integer * ) r) -> i;
      }
   } else if ((l -> nodetype == 'N' && r -> nodetype == 'D')) {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct integer * ) tempName) -> i * ((struct doublePrecision * ) r) -> d;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d * ((struct doublePrecision * ) r) -> d;
      }
   } else if ((l -> nodetype == 'N' && r -> nodetype == 'N')) {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i' && ((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i * ((struct integer * ) tempName2) -> i;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'i' && ((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct integer * ) tempName) -> i * ((struct doublePrecision * ) tempName2) -> d;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D' && ((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d * ((struct integer * ) tempName2) -> i;
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D' && ((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) tempName) -> d * ((struct doublePrecision * ) tempName2) -> d;
      }
   } else {
      yyerror("Unexpected type, %c %c", l -> nodetype, r -> nodetype);
   }
}

struct utils *
divide(struct utils * l, struct utils * r) {
   struct utils * tempName, * tempName2;
   struct utils * v;
   v=malloc(sizeof(struct doublePrecision));
   ((struct doublePrecision * ) v) -> nodetype = 'D';
   
   if (l -> nodetype == 'i' && r -> nodetype == 'D') {
      if(((struct doublePrecision * ) r) -> d !=0){
         ((struct doublePrecision *)v) -> d = ((struct integer * ) l) -> i / ((struct doublePrecision * ) r) -> d;
      }
   } else if (l -> nodetype == 'D' && r -> nodetype == 'i') {
      if(((struct integer * ) r) -> i !=0){
         ((struct doublePrecision *)v) -> d = ((struct doublePrecision * ) l) -> d / ((struct integer * ) r) -> i;
      }
   } else if (l -> nodetype == 'i' && r -> nodetype == 'i') {
      if(((struct integer * ) r) -> i !=0){
         ((struct doublePrecision *)v) -> d = (double) (((struct integer * ) l) -> i) / (double)(((struct integer * ) r) -> i);
      }
   } else if (l -> nodetype == 'D' && r -> nodetype == 'D') {
      if(((struct doublePrecision * ) r) -> d !=0){
         ((struct doublePrecision *)v) -> d = ((struct doublePrecision * ) l) -> d / ((struct doublePrecision * ) r) -> d;
      }
   } else if ((l -> nodetype == 'i' && r -> nodetype == 'N')) {
      if (((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) r) -> s -> value;
         if(((struct integer *)tempName)->i != 0){
            ((struct doublePrecision *)v) -> d = ((struct integer * ) l) -> i / ((struct integer * ) tempName) -> i;
         }
      } else if (((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) r) -> s -> value;
         if(((struct doublePrecision *)tempName)->d != 0){
            ((struct doublePrecision *)v) -> d = ((struct integer * ) l) -> i / ((struct doublePrecision * ) tempName) -> d;
         }
      }
   } else if ((l -> nodetype == 'D' && r -> nodetype == 'N')) {
      if (((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) r) -> s -> value;
         if(((struct integer *)tempName)->i !=0){
            ((struct doublePrecision *)v) -> d = ((struct doublePrecision * ) l) -> d / ((struct integer * ) tempName) -> i;
         }
      } else if (((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) r) -> s -> value;
         if(((struct doublePrecision *)tempName)->d !=0){
            ((struct doublePrecision *)v) -> d = ((struct doublePrecision * ) l) -> d / ((struct doublePrecision * ) tempName) -> d;
         }
      }
   } else if (l -> nodetype == 'N' && r -> nodetype == 'i') {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         if(((struct integer *)tempName)->i !=0){
            ((struct doublePrecision *)v) -> d = ((struct integer * ) tempName) -> i / ((struct integer * ) r) -> i;
         }
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         if(((struct doublePrecision *)tempName)->d !=0){
            ((struct doublePrecision *)v) -> d = ((struct doublePrecision * ) tempName) -> d / ((struct integer * ) r) -> i;
         }
      }
   } else if ((l -> nodetype == 'N' && r -> nodetype == 'D')) {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         if(((struct integer *)tempName)->i !=0){
            ((struct doublePrecision *)v) -> d = ((struct integer * ) tempName) -> i / ((struct doublePrecision * ) r) -> d;
         }
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         if(((struct doublePrecision *)tempName)->d !=0){
            ((struct doublePrecision *)v) -> d = ((struct doublePrecision * ) tempName) -> d / ((struct doublePrecision * ) r) -> d;
         }
      }
   } else if ((l -> nodetype == 'N' && r -> nodetype == 'N')) {
      if (((struct symref * ) l) -> s -> value -> nodetype == 'i' && ((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         if(((struct integer *)tempName)->i !=0){
            ((struct doublePrecision *)v) -> d = ((struct integer * ) tempName) -> i / ((struct integer * ) tempName2) -> i;
         }
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'i' && ((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         if(((struct doublePrecision *)tempName)->d !=0){
            ((struct doublePrecision *)v) -> d = ((struct integer * ) tempName) -> i / ((struct doublePrecision * ) tempName2) -> d;
         }
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D' && ((struct symref * ) r) -> s -> value -> nodetype == 'i') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         if(((struct integer *)tempName)->i !=0){
            ((struct doublePrecision *)v) -> d = ((struct doublePrecision * ) tempName) -> d / ((struct integer * ) tempName2) -> i;
         }
      } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D' && ((struct symref * ) r) -> s -> value -> nodetype == 'D') {
         tempName = ((struct symref * ) l) -> s -> value;
         tempName2 = ((struct symref * ) r) -> s -> value;
         if(((struct doublePrecision *)tempName)->d !=0){
            ((struct doublePrecision *)v) -> d = ((struct doublePrecision * ) tempName) -> d / ((struct doublePrecision * ) tempName2) -> d;
         }
      }
   } else {
      yyerror("Unexpected type, %c %c", l -> nodetype, r -> nodetype);
   }
   return v;
}

void
absoluteValue(struct utils * v, struct utils * l) {
   struct utils * tempName;

   if (l -> nodetype == 'N') {
      tempName = ((struct symref * ) l) -> s -> value;

      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = abs(((struct integer * ) tempName) -> i);
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct doublePrecision * ) v) -> d = fabs(((struct doublePrecision * ) tempName) -> d);
      }
   } else if (v -> nodetype == 'i') {
      ((struct integer * ) v) -> i = abs(((struct integer * ) l) -> i);
   } else if (v -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = fabs(((struct doublePrecision * ) l) -> d);
   } 
}

void
biggerThan(struct utils * v, struct utils * l, struct utils * r) {
   struct utils * tempName, * tempName2;

   if(l ->nodetype == 'N' && r->nodetype == 'i'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i > ((struct integer * ) r) -> i ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d > ((struct integer * ) r) -> i ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'D'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i > ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d > ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'i' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i > ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i > ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'D' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d > ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d > ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'N'){
      tempName = ((struct symref * ) l) -> s -> value;
      tempName2 = ((struct symref * ) r) -> s -> value;
      if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i > ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i > ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d > ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d > ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }
   }else if (l -> nodetype == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i > ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d > ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i > ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d > ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }
}

void
smallerThan(struct utils * v, struct utils * l, struct utils * r) {
   struct utils * tempName, * tempName2;

   if(l ->nodetype == 'N' && r->nodetype == 'i'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i < ((struct integer * ) r) -> i ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d < ((struct integer * ) r) -> i ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'D'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i < ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d < ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'i' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i < ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i < ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'D' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d < ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d < ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'N'){
      tempName = ((struct symref * ) l) -> s -> value;
      tempName2 = ((struct symref * ) r) -> s -> value;
      if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i < ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i < ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d < ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d < ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }
   }else if (l -> nodetype == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i < ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d < ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i < ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d < ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }
}

void
unequal(struct utils * v, struct utils * l, struct utils * r) {
   struct utils * tempName, * tempName2;

   if(l ->nodetype == 'N' && r->nodetype == 'i'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i != ((struct integer * ) r) -> i ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d != ((struct integer * ) r) -> i ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'D'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i != ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d != ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }
     }else if(l ->nodetype == 'N' && r->nodetype == 'S'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'S'){
         int temp;
         temp = strcmp(strdup(((struct str *)tempName)->str),strdup(((struct str *)r)->str));
         if(temp!=0){
            temp=1;
         }
         ((struct integer * ) v) -> i = temp;
      }
   }else if(l ->nodetype == 'i' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i != ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i != ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'D' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d != ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d != ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'S' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'S'){
         int temp;
         temp = strcmp(strdup(((struct str *)tempName)->str),strdup(((struct str *)l)->str));
         if(temp!=0){
            temp=1;
         }
         ((struct integer * ) v) -> i = temp;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'N'){
      tempName = ((struct symref * ) l) -> s -> value;
      tempName2 = ((struct symref * ) r) -> s -> value;
      if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i != ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i != ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d != ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d != ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'S') && (((struct symref * ) r) -> s -> value -> nodetype == 'S')){
         int temp;
         temp = strcmp(strdup(((struct str *)tempName)->str),strdup(((struct str *)tempName2)->str));
         if(temp!=0){
            temp=1;
         }
         ((struct integer * ) v) -> i = temp;
      }
   }else if (l -> nodetype == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i != ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d != ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i != ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d != ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l -> nodetype == 'S' && r->nodetype == 'S'){
      int temp;
      temp = strcmp(strdup(((struct str *)l)->str),strdup(((struct str *)r)->str));
      if(temp!=0){
         temp=1;
      }
      ((struct integer * ) v) -> i = temp;
   }
}

void
equal(struct utils * v, struct utils * l, struct utils * r) {
   struct utils * tempName, * tempName2;

   if(l ->nodetype == 'N' && r->nodetype == 'i'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i == ((struct integer * ) r) -> i ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d == ((struct integer * ) r) -> i ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'D'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i == ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d == ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'S'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'S'){
         int temp;
         temp = strcmp(strdup(((struct str *)tempName)->str),strdup(((struct str *)r)->str));
         temp=getTruth(temp);
         ((struct integer * ) v) -> i = temp;
      }
   }else if(l ->nodetype == 'i' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i == ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i == ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'D' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d == ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d == ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'S' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'S'){
         int temp;
         temp = strcmp(strdup(((struct str *)tempName)->str),strdup(((struct str *)l)->str));
         temp=getTruth(temp);
         ((struct integer * ) v) -> i = temp;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'N'){
      tempName = ((struct symref * ) l) -> s -> value;
      tempName2 = ((struct symref * ) r) -> s -> value;
      if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i == ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i == ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d == ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d == ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'S') && (((struct symref * ) r) -> s -> value -> nodetype == 'S')){
         int temp;
         temp = strcmp(strdup(((struct str *)tempName)->str),strdup(((struct str *)tempName2)->str));
         temp=getTruth(temp);
         ((struct integer * ) v) -> i = temp;
      }
   }else if (l -> nodetype == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i == ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d == ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i == ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d == ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l -> nodetype == 'S' && r->nodetype == 'S'){
      int temp;
      temp = strcmp(strdup(((struct str *)l)->str),strdup(((struct str *)r)->str));
      temp=getTruth(temp);
      ((struct integer * ) v) -> i = temp;
   }
}

void
biggerOrEqual(struct utils * v, struct utils * l, struct utils * r) {
   struct utils * tempName, * tempName2;

   if(l ->nodetype == 'N' && r->nodetype == 'i'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i >= ((struct integer * ) r) -> i ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d >= ((struct integer * ) r) -> i ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'D'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i >= ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d >= ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'i' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i >= ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i >= ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'D' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d >= ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d >= ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'N'){
      tempName = ((struct symref * ) l) -> s -> value;
      tempName2 = ((struct symref * ) r) -> s -> value;
      if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i >= ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i >= ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d >= ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d >= ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }
   }else if (l -> nodetype == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i >= ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d >= ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i >= ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d >= ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }
}

void
smallerOrEqual(struct utils * v, struct utils * l, struct utils * r) {
   struct utils * tempName, * tempName2;

   if(l ->nodetype == 'N' && r->nodetype == 'i'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i <= ((struct integer * ) r) -> i ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d <= ((struct integer * ) r) -> i ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'D'){
      tempName = ((struct symref * ) l) -> s -> value;
      if(((struct symref * ) l) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i <= ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }else if(((struct symref * ) l) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d <= ((struct doublePrecision * ) r) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'i' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i <= ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i <= ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'D' && r->nodetype == 'N'){
      tempName = ((struct symref * ) r) -> s -> value;
      if(((struct symref * ) r) -> s -> value -> nodetype == 'i'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d <= ((struct integer * ) tempName) -> i ? 1 : 0;
      }else if(((struct symref * ) r) -> s -> value -> nodetype == 'D'){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d <= ((struct doublePrecision * ) tempName) -> d ? 1 : 0;
      }
   }else if(l ->nodetype == 'N' && r->nodetype == 'N'){
      tempName = ((struct symref * ) l) -> s -> value;
      tempName2 = ((struct symref * ) r) -> s -> value;
      if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i <= ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'i') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct integer * ) tempName) -> i <= ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'i')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d <= ((struct integer * ) tempName2) -> i ? 1 : 0;
      }else if((((struct symref * ) l) -> s -> value -> nodetype == 'D') && (((struct symref * ) r) -> s -> value -> nodetype == 'D')){
         ((struct integer * ) v) -> i = ((struct doublePrecision * ) tempName) -> d <= ((struct doublePrecision * ) tempName2) -> d ? 1 : 0;
      }
   }else if (l -> nodetype == 'i' && r->nodetype == 'D') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i <= ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }else if (l->nodetype == 'D' && r->nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d <= ((struct integer * ) r) -> i ? 1 : 0;
   }else if (l->nodetype == 'i' && r->nodetype == 'i'){
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i <= ((struct integer * ) r) -> i ? 1 : 0;
   }else if(l->nodetype == 'D' && r->nodetype == 'D'){
      ((struct integer * ) v) -> i = ((struct doublePrecision * ) l) -> d <= ((struct doublePrecision * ) r) -> d ? 1 : 0;
   }
}