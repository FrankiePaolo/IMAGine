/* calculator with AST */

%{
#  include <stdio.h>
#  include <stdlib.h>
#  include <vips/vips.h>
#  include "utils.h"
%}

%union {
  struct ast *a;
  double d;
  char * str;
  struct symbol *s;		/* which symbol */
  struct symlist *sl;
  int fn;			/* which function */
}

/* declare tokens */
%token <d> NUMBER
%token <s> NAME
<<<<<<< HEAD
<<<<<<< HEAD
%token <s> PATH
=======
%token <p> PATH
>>>>>>> master
=======
%token <s> PATH
>>>>>>> master
%token <fn> FUNC

%token IF THEN ELSE WHILE DO DEF NUM IMG INFO


%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp stmt list explist
%type <sl> symlist

%start program

%%

stmt: IF exp THEN list           { $$ = newflow('I', $2, $4, NULL); }
   | IF exp THEN list ELSE list  { $$ = newflow('I', $2, $4, $6); }
   | WHILE exp DO list           { $$ = newflow('W', $2, $4, NULL); }
   | exp
;

list: /* nothing */ { $$ = NULL; }
   | stmt ';' list { if ($3 == NULL)
	                $$ = $1;
                      else
			$$ = newast('L', $1, $3);
                    }
   ;

exp: exp CMP exp          { $$ = newcmp($2, $1, $3); }
   | exp '+' exp          { $$ = newast('+', $1,$3); }
   | exp '-' exp          { $$ = newast('-', $1,$3); }
   | exp '*' exp          { $$ = newast('*', $1,$3); }
   | exp '/' exp          { $$ = newast('/', $1,$3); }
   | '|' exp              { $$ = newast('|', $2, NULL); }
   | '(' exp ')'          { $$ = $2; }
   | '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
   | NUMBER               { $$ = newnum($1); }
   | PATH                 { $$ = newref($1); }
   | FUNC '(' explist ')' { $$ = newfunc($1, $3); }
   | NAME                 { $$ = newref($1); }
<<<<<<< HEAD
   | PATH                 { $$ = newref($1); }
   | NAME '=' exp         { $$ = newasgn($1, $3); }
=======
   | NUM NAME '=' exp     { $$ = newasgn($2, $4); }
   | IMG NAME exp         { $$ = newasgn($2,$3); }
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> master
=======
   | INFO NAME            {   }
>>>>>>> master
=======
   | INFO NAME            { ;}
>>>>>>> master
   | NAME '(' explist ')' { $$ = newcall($1, $3); }
;

explist: exp
 | exp ',' explist  { $$ = newast('L', $1, $3); }
;
symlist: NAME       { $$ = newsymlist($1, NULL); }
 | NAME ',' symlist { $$ = newsymlist($1, $3); }
;

program: /* nothing */
  | program stmt  {
    if(debug) dumpast($2, 0);
     printf("= %4.4g\n> ", eval($2));
     treefree($2);
    }
  | program DEF NAME '(' symlist ')' '=' list  {
                       dodef($3, $5, $8);
                       printf("Defined %s\n> ", $3->name); }

  | program error '\n' { yyerrok; printf("> "); }
 ;
%%
