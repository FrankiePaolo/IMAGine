#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#  include <vips/vips.h>
#  include "utils.h"

static struct utils * callbuiltin(struct fncall *f);

/* hash a symbol */
static unsigned
symhash(char *sym)
{
  unsigned int hash = 0;
  unsigned c;

  while(c = *sym++) hash = hash*9 ^ c;

  return hash;
}

struct symbol *
lookup(char* sym)
{
  struct symbol *sp = &symtab[symhash(sym)%NHASH];
  int scount = NHASH;		/* how many have we looked at */

  while(--scount >= 0) {
    if(sp->name && !strcmp(sp->name, sym)) { return sp; }

    if(!sp->name) {		/* new entry */
      sp->name = strdup(sym);
      // TO BE FIXED
      // sp->value = 0; 
      sp->func = NULL;
      sp->syms = NULL;
      return sp;
    }

    if(++sp >= symtab+NHASH) sp = symtab; /* try the next entry */
  }
  yyerror("symbol table overflow\n");
  abort(); /* tried them all, table is full */

}

struct ast *
newast(int nodetype, struct ast *l, struct ast *r)
{
  struct ast *a = malloc(sizeof(struct ast));

  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = nodetype;
  a->l = l;
  a->r = r;
  return a;
}


struct ast *
newint(int i)
{
  struct integer *a = malloc(sizeof(struct integer));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }

  a->nodetype='i';
  a->i=i;
  
  return (struct ast *)a;
}

struct ast *
newdouble(double d)
{
  struct doublePrecision *a = malloc(sizeof(struct doublePrecision));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }

  a->nodetype='D';
  a->d=d;
  
  return (struct ast *)a;
}

struct ast *
newcmp(int cmptype, struct ast *l, struct ast *r)
{
  struct ast *a = malloc(sizeof(struct ast));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = '0' + cmptype;
  a->l = l;
  a->r = r;
  return a;
}

struct ast *
newfunc(int functype, struct ast *l)
{
  struct fncall *a = malloc(sizeof(struct fncall));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = 'F';
  a->l = l;
  a->functype = functype;
  return (struct ast *)a;
}

struct ast *
newcall(struct symbol *s, struct ast *l)
{
  struct ufncall *a = malloc(sizeof(struct ufncall));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = 'C';
  a->l = l;
  a->s = s;
  return (struct ast *)a;
}

struct ast *
newref(struct symbol *s)
{
  struct symref *a = malloc(sizeof(struct symref));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = 'N';
  a->s = s;
  return (struct ast *)a;
}

struct ast *
newasgn(struct symbol *s, struct ast *v)
{
  struct symasgn *a = malloc(sizeof(struct symasgn));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = '=';
  a->s = s;
  a->v = v;
  return (struct ast *)a;
}

struct ast *
newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el)
{
  struct flow *a = malloc(sizeof(struct flow));
  
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = nodetype;
  a->cond = cond;
  a->tl = tl;
  a->el = el;
  return (struct ast *)a;
}

struct symlist *
newsymlist(struct symbol *sym, struct symlist *next)
{
  struct symlist *sl = malloc(sizeof(struct symlist));
  
  if(!sl) {
    yyerror("out of space");
    exit(0);
  }
  sl->sym = sym;
  sl->next = next;
  return sl;
}

void
symlistfree(struct symlist *sl)
{
  struct symlist *nsl;

  while(sl) {
    nsl = sl->next;
    free(sl);
    sl = nsl;
  }
}

/* define a function */
void
dodef(struct symbol *name, struct symlist *syms, struct ast *func){
  if(name->syms) symlistfree(name->syms);
  if(name->func) treefree(name->func);
  name->syms = syms;
  name->func = func;
}


struct utils *  
setNodeType(struct ast * l, struct ast * r){
  struct utils * v;
  if(l->nodetype == 'i' && r->nodetype == 'i'){
    v = malloc(sizeof(struct integer));
    ((struct integer *)v)->nodetype='i';
  }else if (l->nodetype == 'D' && r->nodetype == 'D'){
    v = malloc(sizeof(struct doublePrecision));
    ((struct doublePrecision *)v)->nodetype='D';
  }else{
    yyerror("Unexpected type, %c %c",l->nodetype,r->nodetype);
  }

  if(v==NULL){
    yyerror("out of space");
    exit(0);
  }
  return v;
}

void
sum(int nodetype,struct ast *l,struct ast *r){
    if (nodetype=='i'){
      ((struct integer *)v)->i = ((struct integer *)eval(a->l))->i + ((struct integer *)eval(a->r))->i; break;
    }else if (nodetype=='D'){
      ((struct doublePrecision *)v)->d = ((struct doublePrecision *)eval(a->l))->d + ((struct doublePrecision *)eval(a->r))->d; break;
    }
}


struct utils *
eval(struct ast *a)
{
  struct utils *v;

  struct utils *temp1;
  struct utils *temp2;

  if(!a) {
    yyerror("internal error, null eval");
    // add return condition
  }

  switch(a->nodetype) {

    /* int */
  case 'i': 
    v = malloc(sizeof(struct integer));
    v->nodetype='i';
    ((struct integer *)v)->i = ((struct integer *)a)->i; break;

    /* double */
  case 'D': 
    v = malloc(sizeof(struct doublePrecision));
    v->nodetype='D';
    ((struct doublePrecision *)v)->d = ((struct doublePrecision *)a)->d; break;

    /* name reference */
  case 'N': ((struct symref *)v)->s->value = ((struct symref *)a)->s->value; break;

    /* assignment */
  case '=': v = ((struct symasgn *)a)->s->value =
      eval(((struct symasgn *)a)->v); break;

    /* expressions */
  case '+': 
    temp1=eval(a->l);
    temp2=eval(a->r);

    v=setNodeType(temp1,temp2);
    sum(v->nodetype,temp1,temp2);

  case '-': 
    break;

  case '*': 
    break;

  case '/': 
    break;  
    
  case '|':
   if (v->nodetype=='T'){
        fabs(((struct integer *)eval(a->l))->i); break;

    }else if(v->nodetype=='K'){
        fabs(((struct doublePrecision *)eval(a->l))->d); break;
    }  

    /* comparisons */
  case '1': 
    if (v->nodetype=='T'){
     ((struct integer *)v)->i = (((struct integer *)eval(a->l))->i > ((struct integer *)eval(a->r))->i)? 1 : 0; break; 
    }else if(v->nodetype=='K'){
     ((struct doublePrecision *)v)->d = (((struct doublePrecision *)eval(a->l))->d > ((struct doublePrecision *)eval(a->r))->d)? 1 : 0; break; 
    }  

  case '2': 
    if (v->nodetype=='T'){
     ((struct integer *)v)->i = (((struct integer *)eval(a->l))->i < ((struct integer *)eval(a->r))->i)? 1 : 0; break; 
    }else if(v->nodetype=='K'){
     ((struct doublePrecision *)v)->d = (((struct doublePrecision *)eval(a->l))->d < ((struct doublePrecision *)eval(a->r))->d)? 1 : 0; break; 
    }  
  
  case '3': 
    if (v->nodetype=='T'){
     ((struct integer *)v)->i = (((struct integer *)eval(a->l))->i != ((struct integer *)eval(a->r))->i)? 1 : 0; break; 
    }else if(v->nodetype=='K'){
     ((struct doublePrecision *)v)->d = (((struct doublePrecision *)eval(a->l))->d != ((struct doublePrecision *)eval(a->r))->d)? 1 : 0; break; 
    }  
    
  case '4': 
    if (v->nodetype=='T'){
     ((struct integer *)v)->i = (((struct integer *)eval(a->l))->i == ((struct integer *)eval(a->r))->i)? 1 : 0; break; 
    }else if(v->nodetype=='K'){
     ((struct doublePrecision *)v)->d = (((struct doublePrecision *)eval(a->l))->d == ((struct doublePrecision *)eval(a->r))->d)? 1 : 0; break; 
    }  

  case '5': 
    if (v->nodetype=='T'){
     ((struct integer *)v)->i = (((struct integer *)eval(a->l))->i >= ((struct integer *)eval(a->r))->i)? 1 : 0; break; 
    }else if(v->nodetype=='K'){
     ((struct doublePrecision *)v)->d = (((struct doublePrecision *)eval(a->l))->d >= ((struct doublePrecision *)eval(a->r))->d)? 1 : 0; break; 
    }  

  case '6': 
    if (v->nodetype=='T'){
     ((struct integer *)v)->i = (((struct integer *)eval(a->l))->i <= ((struct integer *)eval(a->r))->i)? 1 : 0; break; 
    }else if(v->nodetype=='K'){
     ((struct doublePrecision *)v)->d = (((struct doublePrecision *)eval(a->l))->d <= ((struct doublePrecision *)eval(a->r))->d)? 1 : 0; break; 
    }  
  
  /* control flow */
  /* null if/else/do expressions allowed in the grammar, so check for them */
  case 'I': 
    if( eval( ((struct flow *)a)->cond) != 0) {

      if( ((struct flow *)a)->tl) {
	      v = eval( ((struct flow *)a)->tl);
      } else{
	      ((struct doublePrecision *)v)->d = 0.0;		/* a default value */
      } 

      if( ((struct flow *)a)->el) {
        v = eval(((struct flow *)a)->el);
      } else {
	      ((struct doublePrecision *)v)->d = 0.0;		/* a default value */
      }

    }
    break;
    
  case 'F': v = callbuiltin((struct fncall *)a); break;

  case 'W':

    ((struct doublePrecision *)v)->d = 0.0;		/* a default value */

    if( ((struct flow *)a)->tl) {
      while (eval(((struct flow *)a)->cond) != 0){
	      v = eval(((struct flow *)a)->tl);
      }
    }
    break;			/* last value is value */
	              
  case 'L': eval(a->l); v = eval(a->r); break;

  case 'C': ((struct doublePrecision *)v)->d = calluser((struct ufncall *)a); break;

  default: printf("internal error: bad node %c\n", a->nodetype);
  }
  
  return v;
}

static struct utils *
callbuiltin(struct fncall *f)
{
  enum bifs functype = f->functype;
  struct utils * v = eval(f->l);

 switch(functype) {
 case B_print:
   print_B(v);
   return v;
 default:
   yyerror("Unknown built-in function %d", functype);
   return NULL;
 }
}

void 
print_B(struct utils * v){
  if (v->nodetype=='i'){
    printf("%d\n",((struct integer *)v)->i);  
  }else if (v->nodetype=='D'){
    printf("%f\n",((struct doublePrecision *)v)->d);  
  }
}

double
calluser(struct ufncall *f)
{
  struct symbol *fn = f->s;	/* function name */
  struct symlist *sl;		/* dummy arguments */
  struct ast *args = f->l;	/* actual arguments */
  double *oldval, *newval;	/* saved arg values */
  double v;
  int nargs;
  int i;

  if(!fn->func) {
    yyerror("call to undefined function", fn->name);
    return 0;
  }

  /* count the arguments */
  sl = fn->syms;
  for(nargs = 0; sl; sl = sl->next)
    nargs++;

  /* prepare to save them */
  oldval = (double *)malloc(nargs * sizeof(double));
  newval = (double *)malloc(nargs * sizeof(double));
  if(!oldval || !newval) {
    yyerror("Out of space in %s", fn->name);
  }
  
  /* evaluate the arguments */
  for(i = 0; i < nargs; i++) {
    if(!args) {
      yyerror("too few args in call to %s", fn->name);
      free(oldval); free(newval);
      return 0;
    }

    if(args->nodetype == 'L') {	/* if this is a list node */
      newval[i] = ((struct doublePrecision *)eval(args->l))->d;
      args = args->r;
    } else {			/* if it's the end of the list */
      newval[i] = ((struct doublePrecision *)eval(args))->d;
      args = NULL;
    }
  }
		     
  /* save old values of dummies, assign new ones */
  sl = fn->syms;
  for(i = 0; i < nargs; i++) {
    struct symbol *s = sl->sym;

    oldval[i] = ((struct doublePrecision *)s->value)->d;
    ((struct doublePrecision *)s->value)->d = newval[i];
    sl = sl->next;
  }

  free(newval);

  /* evaluate the function */
  v = ((struct doublePrecision *)eval(fn->func))->d;

  /* put the dummies back */
  sl = fn->syms;
  for(i = 0; i < nargs; i++) {
    struct symbol *s = sl->sym;

    ((struct doublePrecision *)s->value)->d = oldval[i];
    sl = sl->next;
  }

  free(oldval);
  return v;
}


void
treefree(struct ast *a)
{
  switch(a->nodetype) {

    /* two subtrees */
  case '+':
  case '-':
  case '*':
  case '/':
  case '1':  case '2':  case '3':  case '4':  case '5':  case '6':
  case 'L':
    treefree(a->r);

    /* one subtree */
  case '|':
  case 'M': case 'C': case 'F': 
    treefree(a->l);

    /* no subtree */
  case 'i': case 'N': case 'D':
    break;

  case '=':
    free( ((struct symasgn *)a)->v);
    break;

  case 'I': case 'W':
    free( ((struct flow *)a)->cond);
    if( ((struct flow *)a)->tl) free( ((struct flow *)a)->tl);
    if( ((struct flow *)a)->el) free( ((struct flow *)a)->el);
    break;

  default: printf("internal error: free bad node %c\n", a->nodetype);
  }	  
  
  free(a); /* always free the node itself */

}

void
yyerror(char *s, ...)
{
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

int
main(int argc, char *argv[])
{
  if( VIPS_INIT( argv[0] ) ) {
  /* This shows the vips error buffer and quits with a fail exit
         * code.
         */
    vips_error_exit( NULL ); 
  }
  printf("> "); 
  return yyparse();
}

/* debugging: dump out an AST */
int debug = 0;
void
dumpast(struct ast *a, int level)
{

  printf("%*s", 2*level, "");	/* indent to this level */
  level++;

  if(!a) {
    printf("NULL\n");
    return;
  }

  switch(a->nodetype) {
  case 'i': printf("number %4.4g\n", ((struct integer *)a)->i); break;
  
    /* double precision */
  case 'D': printf("number %4.4g\n", ((struct doublePrecision *)a)->d); break;

    /* name reference */
  case 'N': printf("ref %s\n", ((struct symref *)a)->s->name); break;

    /* assignment */
  case '=': printf("= %s\n", ((struct symref *)a)->s->name);
    dumpast( ((struct symasgn *)a)->v, level); return;

    /* expressions */
  case '+': case '-': case '*': case '/': case 'L':
  case '1': case '2': case '3':
  case '4': case '5': case '6': 
    printf("binop %c\n", a->nodetype);
    dumpast(a->l, level);
    dumpast(a->r, level);
    return;

  case '|': case 'M': 
    printf("unop %c\n", a->nodetype);
    dumpast(a->l, level);
    return;

  case 'I': case 'W':
    printf("flow %c\n", a->nodetype);
    dumpast( ((struct flow *)a)->cond, level);
    if( ((struct flow *)a)->tl)
      dumpast( ((struct flow *)a)->tl, level);
    if( ((struct flow *)a)->el)
      dumpast( ((struct flow *)a)->el, level);
    return;

  case 'C': printf("call %s\n", ((struct ufncall *)a)->s->name);
    dumpast(a->l, level);
    return;

  default: printf("bad %c\n", a->nodetype);
    return;
    
  }
}
