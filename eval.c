#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "builtin.h"
#include "eval.h"
#include "operations.h"

struct utils *
   eval(struct ast * a) {
      struct utils * v;

      struct utils * temp1;
      struct utils * temp2;

      if (!a) {
         yyerror("internal error, null eval");
         exit(0);
      }

      switch (a -> nodetype) {
   
      case 'M':            /* unary minus, negative value */
         if(a->l->nodetype=='i'){
            int temp;
            temp=((struct integer *)(a->l))->i;
            ((struct integer *)(a->l))->i=-temp;
            v=a->l;
         }else if(a->l->nodetype=='D'){
            double temp;
            temp=((struct doublePrecision *)(a->l))->d;
            ((struct doublePrecision *)(a->l))->d=-temp;
            v=a->l;
         }
         break;

      case 'S':    /* string */
      case 'i':    /* int */
      case 'D':    /* double */
      case 'P':    /* picture */
      case 'N':    /* name reference */
         v = ((struct utils *)a) ;
         break;

         /* assignment */
      case '=':
         temp1 = eval(((struct symasgn *)a)->v);
         ((struct symasgn * ) a) -> s ->value = temp1;
         v = ((struct utils *)a) ;
         break;

         /* operations */
      case '+':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);
         v = setNodeType(temp1, temp2);
         sum(v, temp1, temp2);
         break;

      case '-':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v = setNodeType(temp1, temp2);
         subtract(v, temp1, temp2);
         break;

      case '*':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v = setNodeType(temp1, temp2);
         multiply(v, temp1, temp2);
         break;

      case '/':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v=divide(temp1, temp2);
         break;

      case '|':
         temp1 = eval(a -> l);
         temp2 = NULL;

         v = setNodeType(temp1, temp2);
         absoluteValue(v, temp1);
         break;

         /* comparisons */
      case '1':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v = setNodeType(temp1, temp2);
         biggerThan(v, temp1, temp2);
         break;

      case '2':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v = setNodeType(temp1, temp2);
         smallerThan(v, temp1, temp2);
         break;

      case '3':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v = setNodeType(temp1, temp2);
         unequal(v, temp1, temp2);
         break;

      case '4':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v = setNodeType(temp1, temp2);
         equal(v, temp1, temp2);
         break;

      case '5':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v = setNodeType(temp1, temp2);
         biggerOrEqual(v, temp1, temp2);
         break;

      case '6':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v = setNodeType(temp1, temp2);
         smallerOrEqual(v, temp1, temp2);
         break;

         /* control flow */
         /* null if/else/do expressions allowed in the grammar, so we check for them */
      case 'I':
         if((((struct integer *)eval(((struct flow * ) a) -> cond))->i) == 1){
            if (((struct flow * ) a) -> tl) {
               v = eval(((struct flow * ) a) -> tl);
            }
         }else{
            if (((struct flow * ) a) -> el) {
               v = eval(((struct flow * ) a) -> el);
            }         
         }
         break;

      case 'F':
         v = callbuiltin((struct fncall * ) a);
         break;

      case 'W':
         if (((struct flow * ) a) -> tl) {
            while ((((struct integer *)eval(((struct flow * ) a) -> cond))->i) == 1) {
               v = eval(((struct flow * ) a) -> tl);
            }
         }
         break; 

      case 'L':
         eval(a -> l);
         v = eval(a -> r);
         break;

      case 'C':
         v = calluser((struct ufncall * ) a);
         break;

      default:
         printf("internal error: bad node %c\n", a -> nodetype);
      }

      return v;
   }