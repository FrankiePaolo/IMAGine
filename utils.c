#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#  include <vips/vips.h>
#  include "utils.h"

static struct utils * callbuiltin(struct fncall * f);

/* hash a symbol */
static unsigned
symhash(char * sym) {
   unsigned int hash = 0;
   unsigned c;

   while (c = * sym++) hash = hash * 9 ^ c;

   return hash;
}

struct symbol *
   lookup(char * sym) {
      struct symbol * sp = & symtab[symhash(sym) % NHASH];
      int scount = NHASH; /* how many have we looked at */

      while (--scount >= 0) {
         if (sp -> name && !strcmp(sp -> name, sym)) {
            return sp;
         }

         if (!sp -> name) {
            /* new entry */
            sp -> name = strdup(sym);
            sp -> value = NULL;
            sp -> func = NULL;
            sp -> syms = NULL;
            return sp;
         }

         if (++sp >= symtab + NHASH) {
            sp = symtab; /* try the next entry */
         }
      }
      yyerror("symbol table overflow\n");
      abort(); /* tried them all, table is full */

   }

struct ast *
   newast(int nodetype, struct ast * l, struct ast * r) {
      struct ast * a = malloc(sizeof(struct ast));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }
      a -> nodetype = nodetype;
      a -> l = l;
      a -> r = r;
      return a;
   }

struct ast *
   newimg(char * path) {
      struct img * a = malloc(sizeof(struct img));
      VipsImage * in ;
      /*
      char * correctPath;
      strncpy(correctPath,path,strlen(path)-1);*/

      if (!a) {
         yyerror("out of space");
         exit(0);
      }

      a -> nodetype = 'P'; //P as in picture
      path++;
      a -> path = path;

      if (!( in = vips_image_new_from_file(path, NULL))) {
         vips_error_exit(NULL);
      }

      a -> img = in ;
      return (struct ast * ) a;

   }

struct ast *
   newint(int i) {
      struct integer * a = malloc(sizeof(struct integer));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }

      a -> nodetype = 'i';
      a -> i = i;

      return (struct ast * ) a;
   }

struct ast *
   newdouble(double d) {
      struct doublePrecision * a = malloc(sizeof(struct doublePrecision));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }

      a -> nodetype = 'D';
      a -> d = d;

      return (struct ast * ) a;
   }

struct ast *
   newcmp(int cmptype, struct ast * l, struct ast * r) {
      struct ast * a = malloc(sizeof(struct ast));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }
      a -> nodetype = '0' + cmptype;
      a -> l = l;
      a -> r = r;
      return a;
   }

struct ast *
   newfunc(int functype, struct ast * l) {
      struct fncall * a = malloc(sizeof(struct fncall));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }
      a -> nodetype = 'F';
      a -> l = l;
      a -> functype = functype;
      return (struct ast * ) a;
   }

struct ast *
   newcall(struct symbol * s, struct ast * l) {
      struct ufncall * a = malloc(sizeof(struct ufncall));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }
      a -> nodetype = 'C';
      a -> l = l;
      a -> s = s;
      return (struct ast * ) a;
   }

struct ast *
   newref(struct symbol * s) {
      struct symref * a = malloc(sizeof(struct symref));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }
      a -> nodetype = 'N';
      a -> s = s;
      return (struct ast * ) a;
   }

struct ast *
   newasgn(struct symbol * s, struct ast * v) {
      struct utils * temp;
      struct symasgn * a = malloc(sizeof(struct symasgn));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }
      a -> nodetype = '=';
      a -> s = s;
      a -> v = v;
      if (v -> nodetype == 'C') {
         temp = eval(v);
         s -> value = temp;
      } else {
         s -> value = ((struct utils * ) v);
      }
      return (struct ast * ) a;
   }

struct ast *
   newflow(int nodetype, struct ast * cond, struct ast * tl, struct ast * el) {
      struct flow * a = malloc(sizeof(struct flow));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }
      a -> nodetype = nodetype;
      a -> cond = cond;
      a -> tl = tl;
      a -> el = el;
      return (struct ast * ) a;
   }

struct symlist *
   newsymlist(struct symbol * sym, struct symlist * next) {
      struct symlist * sl = malloc(sizeof(struct symlist));

      if (!sl) {
         yyerror("out of space");
         exit(0);
      }
      sl -> sym = sym;
      sl -> next = next;
      return sl;
   }

void
symlistfree(struct symlist * sl) {
   struct symlist * nsl;

   while (sl) {
      nsl = sl -> next;
      free(sl);
      sl = nsl;
   }
}

/* define a function */
void
dodef(struct symbol * name, struct symlist * syms, struct ast * func) {

   if (name -> syms) {
      symlistfree(name -> syms);
   }

   /*
   if(name->func){ 
   treefree(name->func);
   }
   */

   name -> syms = syms;
   name -> func = func;
}

struct utils *
   setNodeTypeCast(struct utils * l, struct utils * r) {
      struct utils * v;

      if ((l -> nodetype == 'i' && r -> nodetype == 'N')) {
         if (((struct symref * ) r) -> s -> value -> nodetype == 'i') {
            v = malloc(sizeof(struct integer));
            ((struct integer * ) v) -> nodetype = 'i';
         } else if (((struct symref * ) r) -> s -> value -> nodetype == 'D') {
            v = malloc(sizeof(struct doublePrecision));
            ((struct doublePrecision * ) v) -> nodetype = 'D';
         }
      } else if ((l -> nodetype == 'D' && r -> nodetype == 'N')) {
         v = malloc(sizeof(struct doublePrecision));
         ((struct doublePrecision * ) v) -> nodetype = 'D';
      } else if (l -> nodetype == 'N' && r -> nodetype == 'i') {
         if (((struct symref * ) l) -> s -> value -> nodetype == 'i') {
            v = malloc(sizeof(struct integer));
            ((struct integer * ) v) -> nodetype = 'i';
         } else if (((struct symref * ) l) -> s -> value -> nodetype == 'D') {
            v = malloc(sizeof(struct doublePrecision));
            ((struct doublePrecision * ) v) -> nodetype = 'D';
         }
      } else if ((l -> nodetype == 'N' && r -> nodetype == 'D')) {
         v = malloc(sizeof(struct doublePrecision));
         ((struct doublePrecision * ) v) -> nodetype = 'D';
      } else if ((l -> nodetype == 'N' && r -> nodetype == 'N')) {
         if (((struct symref * ) l) -> s -> value -> nodetype == 'i' && ((struct symref * ) r) -> s -> value -> nodetype == 'i') {
            v = malloc(sizeof(struct integer));
            ((struct integer * ) v) -> nodetype = 'i';
         } else {
            v = malloc(sizeof(struct doublePrecision));
            ((struct doublePrecision * ) v) -> nodetype = 'D';
         }
      } else {
         yyerror("Unexpected type, %c %c", l -> nodetype, r -> nodetype);
      }
      if (v == NULL) {
         yyerror("out of space");
         exit(0);
      }
      return v;
   }

struct utils *
   setNodeType(struct utils * l, struct utils * r) {
      struct utils * v;
      if (l -> nodetype == 'i' && r == NULL) {
         v = malloc(sizeof(struct integer));
         ((struct integer * ) v) -> nodetype = 'i';
      } else if (l -> nodetype == 'D' && r == NULL) {
         v = malloc(sizeof(struct doublePrecision));
         ((struct doublePrecision * ) v) -> nodetype = 'D';
      } else if ((l -> nodetype == 'i' && r -> nodetype == 'D') || (l -> nodetype == 'D' && r -> nodetype == 'i')) {
         v = malloc(sizeof(struct doublePrecision));
         ((struct doublePrecision * ) v) -> nodetype = 'D';
      } else if (l -> nodetype == 'i' && r -> nodetype == 'i') {
         v = malloc(sizeof(struct integer));
         ((struct integer * ) v) -> nodetype = 'i';
      } else if (l -> nodetype == 'D' && r -> nodetype == 'D') {
         v = malloc(sizeof(struct doublePrecision));
         ((struct doublePrecision * ) v) -> nodetype = 'D';
      } else {
         v = setNodeTypeCast(l, r);
      }
      return v;
   }

void
sum(struct utils * v, struct utils * l, struct utils * r) {
   struct utils * tempName, * tempName2;

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
   } else if ((l -> nodetype == 'i' && r -> nodetype == 'N')) {
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

void
divide(struct utils * v, struct utils * l, struct utils * r) {
   if (v -> nodetype == 'i') {
      int temp = ((struct integer * ) r) -> i;
      if (temp != 0) {
         ((struct integer * ) v) -> i = ((struct integer * ) l) -> i / ((struct integer * ) r) -> i;
      } else {
         yyerror("Cannot divide by zero\n");
         exit(0);
      }
   } else if (v -> nodetype == 'D') {
      double temp = ((struct doublePrecision * ) r) -> d;
      if (temp != 0) {
         ((struct doublePrecision * ) v) -> d = ((struct doublePrecision * ) l) -> d / ((struct doublePrecision * ) r) -> d;
      } else {
         yyerror("Cannot divide by zero\n");
         exit(0);
      }
   } else {
      yyerror("Unexpected type, %i", v -> nodetype);
   }
}

void
absoluteValue(struct utils * v, struct utils * l) {
   if (v -> nodetype == 'i') {
      ((struct integer * ) v) -> i = abs(((struct integer * ) l) -> i);
   } else if (v -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = fabs(((struct doublePrecision * ) l) -> d);
   }
}

void
biggerThan(struct utils * v, struct utils * l, struct utils * r) {
   if (v -> nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i > ((struct integer * ) r) -> i ? 1 : 0;
   } else if (v -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = (((struct doublePrecision * ) l) -> d > ((struct doublePrecision * ) r) -> d) ? 1 : 0;
   }
}

void
smallerThan(struct utils * v, struct utils * l, struct utils * r) {
   if (v -> nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i < ((struct integer * ) r) -> i ? 1 : 0;
   } else if (v -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = (((struct doublePrecision * ) l) -> d < ((struct doublePrecision * ) r) -> d) ? 1 : 0;
   }
}

void
unequal(struct utils * v, struct utils * l, struct utils * r) {
   if (v -> nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i != ((struct integer * ) r) -> i ? 1 : 0;
   } else if (v -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = (((struct doublePrecision * ) l) -> d != ((struct doublePrecision * ) r) -> d) ? 1 : 0;
   }
}

void
equal(struct utils * v, struct utils * l, struct utils * r) {
   if (v -> nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i == ((struct integer * ) r) -> i ? 1 : 0;
   } else if (v -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = (((struct doublePrecision * ) l) -> d == ((struct doublePrecision * ) r) -> d) ? 1 : 0;
   }
}

void
biggerOrEqual(struct utils * v, struct utils * l, struct utils * r) {
   if (v -> nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i >= ((struct integer * ) r) -> i ? 1 : 0;
   } else if (v -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = (((struct doublePrecision * ) l) -> d >= ((struct doublePrecision * ) r) -> d) ? 1 : 0;
   }
}

void
smallerOrEqual(struct utils * v, struct utils * l, struct utils * r) {
   if (v -> nodetype == 'i') {
      ((struct integer * ) v) -> i = ((struct integer * ) l) -> i <= ((struct integer * ) r) -> i ? 1 : 0;
   } else if (v -> nodetype == 'D') {
      ((struct doublePrecision * ) v) -> d = (((struct doublePrecision * ) l) -> d <= ((struct doublePrecision * ) r) -> d) ? 1 : 0;
   }
}

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

         /* name reference */
      case 'N':
         v = malloc(sizeof(struct symref));
         v -> nodetype = 'N';

         ((struct symref * ) v) -> s = ((struct symref * ) a) -> s;
         break;

         /* assignment */
      case '=':
         v = malloc(sizeof(struct symasgn));
         v -> nodetype = '=';

         ((struct symasgn * ) v) -> s = ((struct symasgn * ) a) -> s;
         ((struct symasgn * ) v) -> v = ((struct symasgn * ) a) -> v;
         break;

         /* expressions */
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

         v = setNodeType(temp1, temp2);
         divide(v, temp1, temp2);
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
         /* null if/else/do expressions allowed in the grammar, so check for them */
      case 'I':
         if (eval(((struct flow * ) a) -> cond) != 0) {

            if (((struct flow * ) a) -> tl) {
               v = eval(((struct flow * ) a) -> tl);
            } else {
               ((struct doublePrecision * ) v) -> d = 0.0; /* a default value */
            }

            if (((struct flow * ) a) -> el) {
               v = eval(((struct flow * ) a) -> el);
            } else {
               ((struct doublePrecision * ) v) -> d = 0.0; /* a default value */
            }

         }
         break;

      case 'F':
         v = callbuiltin((struct fncall * ) a);
         break;

      case 'W':

         ((struct doublePrecision * ) v) -> d = 0.0; /* a default value */

         if (((struct flow * ) a) -> tl) {
            while (eval(((struct flow * ) a) -> cond) != 0) {
               v = eval(((struct flow * ) a) -> tl);
            }
         }
         break; /* last value is value */

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

static struct utils *
   callbuiltin(struct fncall * f) {
      enum bifs functype = f -> functype;
      struct utils * v = eval(f -> l);

      switch (functype) {
      case B_print:
         print_B(v);
         return v;
      case I_width:
         getWidth(((struct symref * ) v));
         return v;
      case I_invert:
         invert(((struct symref * ) v));
         return v;
      case I_average:
         average(((struct symref * ) v));
         return v;
      default:
         yyerror("Unknown built-in function %d", functype);
         return NULL;
      }
   }

void
average(struct symref * v) {
   double mean;
   struct utils * temp1 = v -> s -> value;
   if (vips_avg((((struct img * ) temp1) -> img), & mean, NULL)) {
      vips_error_exit(NULL);
   }

   printf("mean pixel value = %g\n", mean);
}

void
invert(struct symref * v) {
   VipsImage * out;
   char path[500];
   struct utils * temp1 = v -> s -> value;
   if (vips_invert((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }

   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
}

void
getWidth(struct symref * v) {
   struct utils * temp1 = v -> s -> value;
   printf("image width = %d\n", vips_image_get_width(((struct img * ) temp1) -> img));
}

void
print_B(struct utils * v) {
   struct utils * temp1;

   if (v -> nodetype == 'i') {
      printf("%d\n", ((struct integer * ) v) -> i);
   } else if (v -> nodetype == 'D') {
      printf("%f\n", ((struct doublePrecision * ) v) -> d);
   } else if (v -> nodetype == 'N') {
      temp1 = ((struct symref * ) v) -> s -> value;
      if (temp1 -> nodetype == 'i') {
         printf("%i\n", ((struct integer * ) temp1) -> i);
      } else if(temp1->nodetype == 'D') {
         printf("%f\n", ((struct doublePrecision * ) temp1) -> d);
      }
   } else {
      printf("Node not found\n");
   }
}

struct utils *
   calluser(struct ufncall * f) {
      struct symbol * fn = f -> s; /* function name */
      struct symlist * sl; /* dummy arguments */
      struct ast * args = f -> l; /* actual arguments */
      struct utils ** oldval, ** newval; /* saved arg values */
      struct utils * v;
      int nargs;
      int i;

      if (!fn -> func) {
         yyerror("call to undefined function", fn -> name);
         return 0;
      }

      /* count the arguments */
      sl = fn -> syms;
      for (nargs = 0; sl; sl = sl -> next) {
         nargs++;
      }

      /* prepare to save them */
      oldval = malloc(sizeof(struct utils * ) * nargs);
      newval = malloc(sizeof(struct utils * ) * nargs);
      if (!oldval || !newval) {
         yyerror("Out of space in %s", fn -> name);
      }

      /* evaluate the arguments */
      for (i = 0; i < nargs; i++) {
         if (!args) {
            yyerror("CALLUSER: Too few args in call to %s", fn -> name);
            free(oldval);
            free(newval);
            exit(1);
         }
         if (args -> nodetype == 'L') {
            /* if this is a list node */
            newval[i] = eval(args -> l);
            args = args -> r;
            //printf("%s\n",fn->func->nodetype);
         } else {
            /* if it's the end of the list */
            newval[i] = eval(args);
            args = NULL;
         }
      }

      /* save old values of dummies, assign new ones */
      sl = fn -> syms;
      for (i = 0; i < nargs; i++) {
         struct symbol * s = sl -> sym;

         oldval[i] = s -> value;
         s -> value = newval[i];
         sl = sl -> next;
      }

      free(newval);

      /* evaluate the function */
      v = eval(fn -> func);

      /* put the dummies back */
      sl = fn -> syms;
      for (i = 0; i < nargs; i++) {
         if (!sl) {
            struct symbol * s = sl -> sym;
            s -> value = oldval[i];
            sl = sl -> next;
         }
      }

      free(oldval);

      return v;
   }

void
treefree(struct ast * a) {
   switch (a -> nodetype) {

      /* two subtrees */
   case '+':
   case '-':
   case '*':
   case '/':
   case '1':
   case '2':
   case '3':
   case '4':
   case '5':
   case '6':
   case 'L':
      treefree(a -> r);

      /* one subtree */
   case '|':
   case 'M':
   case 'C':
   case 'F':
      treefree(a -> l);

      /* no subtree */
   case 'i':
   case 'D':
   case 'N':
      break;

   case '=':
      free(((struct symasgn * ) a) -> v);
      break;

   case 'I':
   case 'W':
      free(((struct flow * ) a) -> cond);
      if (((struct flow * ) a) -> tl) free(((struct flow * ) a) -> tl);
      if (((struct flow * ) a) -> el) free(((struct flow * ) a) -> el);
      break;

   default:
      printf("internal error: free bad node %c\n", a -> nodetype);
   }

   free(a); /* always free the node itself */

}

void
yyerror(char * s, ...) {
   va_list ap;
   va_start(ap, s);

   fprintf(stderr, "%d: error: ", yylineno);
   vfprintf(stderr, s, ap);
   fprintf(stderr, "\n");
}

int
main(int argc, char * argv[]) {
   if (VIPS_INIT(argv[0])) {
      //This shows the vips error buffer and quits with a fail exit code.
      vips_error_exit("unable to start VIPS");
   }

   printf("> ");
   return yyparse();
   vips_shutdown();
   return 0;
}

/* debugging: dump out an AST */
int debug = 0;
void
dumpast(struct ast * a, int level) {

   printf("%*s", 2 * level, ""); /* indent to this level */
   level++;

   if (!a) {
      printf("NULL\n");
      return;
   }

   switch (a -> nodetype) {
   case 'i':
      printf("number %4.4i\n", ((struct integer * ) a) -> i);
      break;

      /* double precision */
   case 'D':
      printf("number %4.4g\n", ((struct doublePrecision * ) a) -> d);
      break;

      /* name reference */
   case 'N':
      printf("ref %s\n", ((struct symref * ) a) -> s -> name);
      break;

      /* assignment */
   case '=':
      printf("= %s\n", ((struct symref * ) a) -> s -> name);
      dumpast(((struct symasgn * ) a) -> v, level);
      return;

      /* expressions */
   case '+':
   case '-':
   case '*':
   case '/':
   case 'L':
   case '1':
   case '2':
   case '3':
   case '4':
   case '5':
   case '6':
      printf("binop %c\n", a -> nodetype);
      dumpast(a -> l, level);
      dumpast(a -> r, level);
      return;

   case '|':
   case 'M':
      printf("unop %c\n", a -> nodetype);
      dumpast(a -> l, level);
      return;

   case 'I':
   case 'W':
      printf("flow %c\n", a -> nodetype);
      dumpast(((struct flow * ) a) -> cond, level);
      if (((struct flow * ) a) -> tl)
         dumpast(((struct flow * ) a) -> tl, level);
      if (((struct flow * ) a) -> el)
         dumpast(((struct flow * ) a) -> el, level);
      return;

   case 'C':
      printf("call %s\n", ((struct ufncall * ) a) -> s -> name);
      dumpast(a -> l, level);
      return;

   default:
      printf("bad %c\n", a -> nodetype);
      return;

   }
}