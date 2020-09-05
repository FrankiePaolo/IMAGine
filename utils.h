# include <vips/vips.h>

   /* symbol table */
   struct symbol {
      /* a variable name */
      char * name;
      struct utils * value;
      struct list * li;   /* list */
      struct ast * func; /* stmt for the function */
      struct symlist * syms; /* list of dummy args */
   };

/* simple symtab of fixed size */
#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol * lookup(char * );

/* list of symbols, for an argument list */
struct symlist {
   struct symbol * sym;
   struct symlist * next;
};

struct symlist * newsymlist(struct symbol * sym, struct symlist * next);
void symlistfree(struct symlist * sl);

/* node types
 *  + - * / |
 *  0-7 comparison ops, bit coded 04 equal, 02 less, 01 greater
 *  L statement list
 *  I IF statement
 *  W WHILE statement
 *  N symbol ref
 *  = assignment
 *  S list of symbols
 *  F built in function call
 *  C user function call
 */

/* nodes in the Abstract Syntax Tree */
/* all have common initial nodetype */

enum bifs {
   /* built-in functions */
   b_print = 1,
      b_width,
      b_add,
      b_subtract,
      b_invert,
      b_average,
      b_push,
      b_pop,
      b_get,
      b_depth,
      b_convert
};

struct ast {
   int nodetype;
   struct ast * l;
   struct ast * r;
};

struct ufncall {
   /* user function */
   int nodetype; /* type C */
   struct ast * l; /* list of arguments */
   struct symbol * s;
};

struct fncall {
   /* built-in function */
   int nodetype; /* type F */
   struct ast * l;
   enum bifs functype;
};

struct flow {
   int nodetype; /* type I or W */
   struct ast * cond; /* condition */
   struct ast * tl; /* then or do list */
   struct ast * el; /* optional else list */
};

struct utils {
   int nodetype;
};

struct integer {
   int nodetype; /* type i */
   int i;
};

struct doublePrecision {
   int nodetype; /* type D */
   double d;
};

/* To be updated , type S 
struct str {
   int nodetype;  
   char * str;
}; 
*/

struct img {
   int nodetype;     /* type P */
   char * path;      /* image path */
   VipsImage * img;
};

struct list {
   // struct utils * e; /* element of list */
   struct symbol * s;   /* element of list */
   struct list *n;   /* pointer to next element */
};

struct symref {
   int nodetype; /* type N */
   struct symbol * s;
};

struct symasgn {
   int nodetype; /* type = */
   struct symbol * s;
   struct ast * v; /* value */
};

/* build an AST */
struct ast * newast(int nodetype, struct ast * l, struct ast * r);
struct ast * newcmp(int cmptype, struct ast * l, struct ast * r);
struct ast * newfunc(int functype, struct ast * l);
struct ast * newcall(struct symbol * s, struct ast * l);
struct ast * newref(struct symbol * s);
struct ast * newasgn(struct symbol * s, struct ast * v);
struct ast * newint(int i);
struct ast * newimg(char * path);
struct ast * newdouble(double i);
struct ast * newflow(int nodetype, struct ast * cond, struct ast * tl, struct ast * tr);

/* build a list */
struct ast * newlist(struct ast * l,struct ast * r);
void dolist(struct symbol * name, struct ast * li);
struct symbol * setList(struct utils * v);

/* define a function */
void dodef(struct symbol * name, struct symlist * syms, struct ast * stmts);

/* call user defined function */
struct utils * calluser(struct ufncall * f);

/* delete and free an AST */
void treefree(struct ast * );

/* set node type */
struct utils * setNodeTypeCast(struct utils * l, struct utils * r);
struct utils * setNodeType(struct utils * l, struct utils * r);

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char * s, ...);

extern int debug;
void dumpast(struct ast * a, int level);