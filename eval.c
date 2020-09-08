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
         /* string */
      case 'S':
         v = malloc(sizeof(struct str));
         v -> nodetype = 'S';
         ((struct str * ) v) -> str = strdup(((struct str * ) a) -> str);
         break;
      

         /* int */
      case 'i':
         v = malloc(sizeof(struct integer));
         v -> nodetype = 'i';
         ((struct integer * ) v) -> i = ((struct integer * ) a) -> i;
         break;

         /* double */
      case 'D':
         v = malloc(sizeof(struct doublePrecision));
         v -> nodetype = 'D';
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) a) -> d;
         break;

         /* picture */
      case 'P':
         v=malloc(sizeof(struct img));
         v->nodetype = 'P';
         ((struct img * ) v) -> img = ((struct img * ) a)-> img;
         ((struct img * ) v) -> path = ((struct img * ) a)-> path;
         break;

         /* name reference */
      case 'N':
         v = malloc(sizeof(struct symref));
         v -> nodetype = 'N';

         ((struct symref * ) v) -> s = ((struct symref * ) a) -> s;
         break;

         /* assignment */
      case '=':
         temp1 = eval(((struct symasgn *)a)->v);
         ((struct symasgn * ) a) -> s ->value = temp1;
         v = ((struct utils *)a) ;
         break;

         ((struct symasgn * ) v) -> s = ((struct symasgn * ) a) -> s;
         ((struct symasgn * ) v) -> v = ((struct symasgn * ) a) -> v;
         ((struct symasgn * ) v) -> s ->value = eval(((struct symasgn *)a)->v);
      
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

         v=((struct utils *)newint(0,'+'));
         biggerThan(v, temp1, temp2);
         break;

      case '2':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v=((struct utils *)newint(0,'+'));
         smallerThan(v, temp1, temp2);
         break;

      case '3':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v=((struct utils *)newint(0,'+'));
         unequal(v, temp1, temp2);
         break;

      case '4':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v=((struct utils *)newint(0,'+'));
         equal(v, temp1, temp2);
         break;

      case '5':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v=((struct utils *)newint(0,'+'));
         biggerOrEqual(v, temp1, temp2);
         break;

      case '6':
         temp1 = eval(a -> l);
         temp2 = eval(a -> r);

         v=((struct utils *)newint(0,'+'));
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
      case 'E':
         if(((struct symref *)((struct flow * ) a)->cond->r)->s->li || ((struct flow * ) a) -> tl){
            struct list * temp_li = ((struct symref *)(((struct flow * ) a)->cond)->r)->s->li;
            struct symref * temp_ref=((struct symref *)((struct flow * ) a)->cond->l);
            do{
               temp_ref->s->value=temp_li->s->value;
               if(((struct flow * ) a) -> tl){
                  v = eval(((struct flow * ) a) -> tl);
               }
            }while((temp_li=temp_li->n));
         }else{
            printf("Li is empty or is not a list\n");
            return 0;
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