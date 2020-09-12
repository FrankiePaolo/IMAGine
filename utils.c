#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#  include <vips/vips.h>
#  include "utils.h"
#  include "builtin.h"
#  include "eval.h"
extern FILE *yyin;

/* hash a symbol */
static unsigned
   symhash(char * sym) {
      unsigned int hash = 0;
      unsigned c;

      while ((c = * sym++)){
         hash = hash * 9 ^ c;
      }
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
            sp -> li = NULL;
            sp -> func = NULL;
            sp -> syms = NULL;
            return sp;
         }

         if (++sp >= symtab + NHASH) {
            sp = symtab; /* try the next entry */
         }
      }
      yyerror("Symbol table overflow!");
      exit(0); /* tried them all, table is full */

   }

char *
getPath(struct ast * p){
   char * path;
   if(p->nodetype=='S'){
      path=strdup(((struct str *)p)->str);
      return path;
   }else if(p->nodetype=='N'){
      return getPath(((struct ast *)getElement_sym((struct utils *)p)));
   }else{
      yyerror("Not a string!");
      exit(0);
   }
}

void
argumentsCheck(struct fncall * f, int index){
   struct ast * node=f->l;
   int counter=1;

   while(node->r && node->nodetype=='L'){
      node=node->r;
      counter++;
   }

   if(counter<index){
      yyerror("Too few arguments for the function! Requested: %d but given: %d!", index, counter);
      exit(0);
   }else if( counter>index){
      yyerror("Too many arguments for the function! Requested: %d but given: %d!", index, counter);
      exit(0);
   }
}

struct ast *
findNode(struct fncall * f, int index){
   struct ast * node=f->l;
   int counter=1;

   while(counter<index){
      if(!(node->r)){
         yyerror("Wrong arguments for the function!");
         exit(0);
      } 
      node=node->r;
      counter++;

      if(!node){
         free(node);
         yyerror("Node does not exist!\n");
         exit(0);
      }
   }

   if(!(node->l)){
         yyerror("Wrong arguments for the function!");
         exit(0);
      } 
   node=node->l;
   return node;
}

int
getTruth(int temp){
   if(temp==0){
      temp=1;
   }else{
      temp=0;
   }
   return temp;
}

int
type(struct utils * v){

	if(v){
  	   return v->nodetype;
	} else {
		yyerror("NULL value detected");
      exit(0);
	}
}

void
putElement_i(struct utils * v,int i){
   if(type(v)=='i'){
      ((struct integer * ) v) -> i=i;
   } else {
		yyerror("NULL value detected");
		return;
	}
}

void
putElement_d(struct utils * v,double d){
   if(type(v)=='D'){
      ((struct doublePrecision * ) v) -> d=d;
   } else {
		yyerror("NULL value detected");
		exit(0);
	}
}

void
putElement_s(struct utils * v,char * s){
   if(type(v)=='S'){
      ((struct str * ) v) -> str=strdup(s);
   } else {
		yyerror("NULL value detected");
		exit(0);
	}
}

int
getElement_i(struct utils * v){
   if(type(v)=='i'){
      return ((struct integer * ) v) -> i ;
   } else if(type(v)=='N') {
      return getElement_i(getElement_sym(v));
   } else{
		yyerror("NULL value detected");
		exit(0);
	}
}

double
getElement_d(struct utils * v){
   if(type(v)=='D'){
      return ((struct doublePrecision * ) v) -> d ;
   } else if(type(v)=='N') {
      return getElement_d(getElement_sym(v));
   } else {
		yyerror("NULL value detected");
		exit(0);
	}
}

char *
getElement_s(struct utils * v){
   if(type(v)=='S'){
      return ((struct str * ) v) -> str ;
   } else if(type(v)=='N') {
      return getElement_s(getElement_sym(v));
   } else {
		yyerror("NULL value detected");
		exit(0);
   }
}

struct utils *
getElement_sym(struct utils * v){
   if(v){
      return ((struct symref * ) v) -> s -> value ;
   } else {
		yyerror("NULL value detected");
		return NULL;
	}
}

struct utils *
getElement_li(struct list * v){
   if(v){
      return v->s->value; 
   } else {
		yyerror("NULL value detected");
		exit(0);
	}
}

struct list *
   getList(struct utils * v){
      if(v){
         return ((struct symref * ) v) -> s->li; 
      } else {
         yyerror("NULL value detected");
		   exit(0);
      }
}

int
   listCheck(struct symref * v){
      if(type((struct utils *)v)=='N' && v->s->li && type( getElement_sym( (struct utils *)v ) ) =='l'){
         return 1;
      } else if(type((struct utils *)v)=='N' && type( getElement_sym( (struct utils *)v ) ) =='l'){
         return 0;
      } else {
         return -1;
      }
}

VipsInterpretation
   getSpace(struct ast * s){
      VipsInterpretation space;
      char * str;
      str=getPath(s);

      if(!strcmp(str,"grey16")){
         space=VIPS_INTERPRETATION_GREY16;   // generic 16-bit mono
      }else if(!strcmp(str,"hsv")){
         space=VIPS_INTERPRETATION_HSV;    // pixels are HSV
      }else if(!strcmp(str,"yxy")){
         space=VIPS_INTERPRETATION_YXY;    // pixels are CIE Yxy
      }else if(!strcmp(str,"lch")){       
         space=VIPS_INTERPRETATION_LCH;    // pixels are in CIE LCh space
      }else if(!strcmp(str,"cmc")){
         space=VIPS_INTERPRETATION_CMC;    // a uniform colourspace based on CMC(1:1)
      }else if(!strcmp(str,"lab")){
         space=VIPS_INTERPRETATION_LAB;    // pixels are in CIE Lab space
      }else {
         yyerror("Wrong space type, check the manual for allowed types!");
         exit(0);
      }
      return space;
}

double
   getValue(struct ast * v){
      double value;
      if(v->nodetype=='i'){
         value=(double)((struct integer *)v)->i;
      }else if(v->nodetype=='D'){
         value=((struct doublePrecision *)v)->d;
      }else if(v->nodetype=='N'){
         return getValue( ((struct ast *)getElement_sym( ((struct utils *)v) )) );
      }else{
         yyerror("The value must be a number!");
         exit(0);
      }
      return value;
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

      if (!a) {
         yyerror("out of space");
         exit(0);
      }

      a -> nodetype = 'P'; //P as in picture
      a -> path = strndup(path,(strlen(path)-1));

      if (!( in = vips_image_new_from_file(a->path, NULL))) {
         vips_error_exit(NULL);
      }

      a -> img = in ;

      return (struct ast * ) a;
   }

struct ast *
   newstring(char * str) {
      struct str * a = malloc(sizeof(struct str));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }

      a -> nodetype = 'S';
      a -> str = strndup(str,(strlen(str)-1));
      return (struct ast * ) a;
   }

struct ast *
   newint(int i,char f) {
      struct integer * a = malloc(sizeof(struct integer));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }

      a -> nodetype = 'i';
      if(f=='-'){
         a -> i = - i;
      }else if(f=='+'){
         a -> i = i;
      }else{
         exit(0);
      }
      return (struct ast * ) a;
   }

struct ast *
   newdouble(double d,char f) {
      struct doublePrecision * a = malloc(sizeof(struct doublePrecision));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }

      a -> nodetype = 'D';
      if(f=='-'){
         a -> d = - d;
      }else if(f=='+'){
         a -> d = d;
      }else{
         exit(0);
      }

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
      if(s->value==NULL){
         a -> s -> value = malloc(sizeof(struct utils *));
         a -> s -> value -> nodetype = 'U';
      }
      return (struct ast * ) a;
   }

struct ast *
   newasgn(struct symbol * s, struct ast * v) {
      struct symasgn * a = malloc(sizeof(struct symasgn));

      if (!a) {
         yyerror("out of space");
         exit(0);
      }
      a -> nodetype = '=';
      a -> s = s;
      a -> v = v;
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

struct ast *
   newlist(struct ast * l,struct ast * r){
      struct list * li=malloc(sizeof(struct list));

      if (!li) {
         yyerror("out of space");
         exit(0);
      }

      if(listCheck((struct symref *) l)!=-1){
         yyerror("Can't add list in declaration, use insert or push!");
         exit(0);
      }

      li->s=setList(((struct utils *)l));
      li->n=((struct list *)r);
      li->nodetype='l';
      return ((struct ast *)li);
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

void 
dolist(struct symbol * name, struct ast * li){
   struct utils * temp=malloc(sizeof(struct utils *));
   temp->nodetype='l';
   name->value=temp;

   name->li=((struct list *)li);
}


// Da togliere se non ci sono errori
struct utils *
   setNodeTypeCast(struct utils * l, struct utils * r) {
      struct utils * v;

     if (type(l) == 'N' && ( r == NULL || type(l) == 'U' ) ) {
         if (type(getElement_sym(l)) == 'i') {
            v = malloc(sizeof(struct integer));
            ((struct integer * ) v) -> nodetype = 'i';
         } else if (type(getElement_sym(l)) == 'D') {
            v = malloc(sizeof(struct doublePrecision));
            ((struct doublePrecision * ) v) -> nodetype = 'D';
         }
      } else if ( (type(l) == 'N' && type(getElement_sym(l)) == 'S') || (type(r) == 'N' && type(getElement_sym(r)) == 'S') ) {
         v = malloc(sizeof(struct str));
         ((struct str * ) v) -> nodetype = 'S';
      } else if ((type(l) == 'i' && type(r) == 'N')) {
         if (type(getElement_sym(r)) == 'i') {
            v = malloc(sizeof(struct integer));
            ((struct integer * ) v) -> nodetype = 'i';
         } else if (type(getElement_sym(r)) == 'D') {
            v = malloc(sizeof(struct doublePrecision));
            ((struct doublePrecision * ) v) -> nodetype = 'D';
         }
      } else if ((type(l) == 'D' && type(r) == 'N')) {
         v = malloc(sizeof(struct doublePrecision));
         ((struct doublePrecision * ) v) -> nodetype = 'D';
      } else if (type(l) == 'N' && type(r) == 'i') {
         if (type(getElement_sym(l)) == 'i') {
            v = malloc(sizeof(struct integer));
            ((struct integer * ) v) -> nodetype = 'i';
         } else if (type(getElement_sym(l)) == 'D') {
            v = malloc(sizeof(struct doublePrecision));
            ((struct doublePrecision * ) v) -> nodetype = 'D';
         }
      } else if ((type(l) == 'N' && type(r) == 'D')) {
         v = malloc(sizeof(struct doublePrecision));
         ((struct doublePrecision * ) v) -> nodetype = 'D';
      } else if ((type(l) == 'N' && type(r) == 'N')) {
         if (type(getElement_sym(l)) == 'i' && type(getElement_sym(r)) == 'i') {
            v = malloc(sizeof(struct integer));
            ((struct integer * ) v) -> nodetype = 'i';
         } else {
            v = malloc(sizeof(struct doublePrecision));
            ((struct doublePrecision * ) v) -> nodetype = 'D';
         }
      } else {
         yyerror("Unexpected type SetNodeType, %c %c", type(l), type(r));
		   exit(0);
      }
      if (v == NULL) {
         yyerror("Out of space");
         exit(0);
      }
      return v;
   }

struct utils *
   setNodeType(struct utils * l, struct utils * r) {
      struct utils * v;
         
      if (type(l) == 'N' &&  r == NULL) {
         return setNodeType(getElement_sym(l), r);
      } else if (type(l) == 'i' &&  r == NULL) {
         v = malloc(sizeof(struct integer));
         ((struct integer * ) v) -> nodetype = 'i';
      } else if (type(l) == 'D' &&  r == NULL) {
         v = malloc(sizeof(struct doublePrecision));
         ((struct doublePrecision * ) v) -> nodetype = 'D';
      } else if ( type(l) == 'i' &&  type(r) == 'i' ) {
         v = malloc(sizeof(struct integer));
         ((struct integer * ) v) -> nodetype = 'i';
      } else if ( ( type(l) == 'D' && ( type(r) == 'D' || type(r) == 0 || type(r) == 'i' )) || ( ( type(l) == 'i' || type(l) == 0 )  && type(r) == 'D' ) ) {
         v = malloc(sizeof(struct doublePrecision));
         ((struct doublePrecision * ) v) -> nodetype = 'D';
      } else if ( type(l) == 'S' || type(r) == 'S' ) {
         v = malloc(sizeof(struct str));
         ((struct str * ) v) -> nodetype = 'S'; 
      } else if ( type(l) == 'N' || type(r) != 'N' ) {
         return setNodeType(getElement_sym(l), r);
      } else if ( type(l) != 'N' || type(r) == 'N' ) {
         return setNodeType(l, getElement_sym(r));
      } else if ( type(l) == 'N' || type(r) == 'N' ) {
         return setNodeType(getElement_sym(l), getElement_sym(r));
      } else if ( type(l) == 'l' || type(r) == 'l' ) {
         yyerror("Cannot perform operations with list, use appropriate method!\n");
         exit(0);
      } else if ( type(l) == 'P' || type(r) == 'P' ) {
         yyerror("Cannot perform operations with image, use appropriate method!\n");
         exit(0);
      } else {
         yyerror("Unexpected type SetNodeType, %c %c", type(l), type(r));
         exit(0);
      } 
      return v;
   }

/* This method allocates a struct symbol with the new value */
struct symbol *
   setList(struct utils * v){ 
      struct symbol * s=malloc(sizeof(struct symbol));

      if(type(v) == 'i'){
         s->value=((struct utils *)newint(((struct integer *)v)->i ,'+'));
      }else if(type(v) == 'D'){
         s->value=((struct utils *)newdouble(((struct doublePrecision *)v)->d,'+'));
      }else if(type(v) == 'S'){
         struct str * a = malloc(sizeof(struct str));
         if (!a) {
            yyerror("out of space");
            exit(0);
         }
         a -> nodetype = 'S';
         a -> str = strndup(  ((struct str *)v)->str,strlen(((struct str *)v)->str)  );
         s->value=((struct utils *)a);
      }else if(type(v) == 'N'){
         s=((struct symref *)v)->s;
      }else{
        yyerror("Nodetype not found");
        exit(0);
      }
      return s;
   }


char *
getFormat(char * path){
   const char delimiters[] = ".";
   char * suffix=NULL;
   char *token = strtok(path, delimiters);
   token = strtok(NULL, delimiters);

   while (token != NULL)
   {
      suffix=strndup(token,(strlen(token)));
      token = strtok(NULL, delimiters);
   }

   return suffix;
}

void
unassignedError(struct utils * temp1){
   if( (type(temp1)== 'N' && type(getElement_sym(temp1))== 'U') ){
      yyerror("Variable '%s' is not assigned! Can't work with unassigned value!", ((struct symref *)temp1)->s->name);
      exit(0);
   }
}

void
imageError(struct ast * v){
   if( ((struct symref * ) v)->nodetype != 'N' ){
      yyerror("The variable is not an image! This method only works with image variables!");
      exit(0);
   }else if( ((struct symref * ) v)->s->value->nodetype!='P') {
      yyerror("Variable '%s' is not an image! This method only works with image variables!", ((struct symref *)v)->s->name);
      exit(0);
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
         yyerror("Call to undefined function", fn -> name);
		   exit(0);
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
		   exit(0);
      }

      /* evaluate the arguments */
      for (i = 0; i < nargs; i++) {
         if (!args) {
            yyerror("CALLUSER: Too few args in call to %s", fn -> name);
            free(oldval);
            free(newval);
            exit(0);
         }
         if (args -> nodetype == 'L') {
            /* if this is a list node */
            newval[i] = eval(args -> l);
            args = args -> r;
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
   case 'C':
   case 'F':
      treefree(a -> l);

      /* no subtree */
   case 'i':
   case 'D':
   case 'N':
   case 'P':
   case 'S':
      break;

   case '=':
      free(((struct symasgn * ) a) -> v);
      break;

   case 'I':
   case 'W':
   case 'E':
      free(((struct flow * ) a) -> cond);
      if (((struct flow * ) a) -> tl) free(((struct flow * ) a) -> tl);
      if (((struct flow * ) a) -> el) free(((struct flow * ) a) -> el);
      break;

   default:
      yyerror("Internal error: free bad node %c\n", a -> nodetype);
      exit(0);
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
   if(argc>1){
      if(!(yyin=fopen(argv[1],"r"))){
         perror(argv[1]);
         return (1);
      }
   }
   yyparse();
   vips_shutdown();
   return 0;
}

/* debugging: dump out an AST ,add S and E*/
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
      printf("number %4.4f\n", ((struct doublePrecision * ) a) -> d);
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

   case 'F':
      printf("builtin %d\n", ((struct fncall *)a)->functype);
      dumpast(a->l, level);
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