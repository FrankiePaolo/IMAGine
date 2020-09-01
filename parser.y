%{
#  include <stdio.h>
#  include <stdlib.h>
#  include <vips/vips.h>
#  include "utils.h"
%}


%union {
  struct ast *a;
  int i;
  double d;
  char * path;
  struct symbol *s;		/* which symbol */
  struct symlist *sl;
  int fn;			      /* which function */
}

/* declare tokens */
%token <i> INT
%token <d> DOUBLE
%token <path> PATH
%token <s> NAME
%token <fn> FUNC
%token EOL

%token IF THEN ELSE WHILE DO DEF IMG


%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' 

%type <a> exp stmt explist img list
%type <sl> symlist

%start program

%%

stmt: IF '(' exp ')' THEN '{' list '}'                    { $$ = newflow('I', $3, $7, NULL); }
   | IF '(' exp ')' THEN '{' list '}' ELSE '{' list '}'   { $$ = newflow('I', $3, $7, $11); }
   | WHILE '(' exp ')' DO '{' list '}'                    { $$ = newflow('W', $3, $7, NULL); }
   | exp ';'
;

list:                               { $$ = NULL; }
   | stmt  list                     { if($2 == NULL){
                                       $$ = $1;
                                    }else{
			                              $$ = newast('L', $1, $2);
                                    }}
;


exp: exp CMP exp          { $$ = newcmp($2, $1, $3); }
   | exp '+' exp          { $$ = newast('+', $1,$3); }
   | exp '-' exp          { $$ = newast('-', $1,$3);}
   | exp '*' exp          { $$ = newast('*', $1,$3); }
   | exp '/' exp          { $$ = newast('/', $1,$3); }
   | '|' exp              { $$ = newast('|', $2, NULL); }
   | '(' exp ')'          { $$ = $2; }
   | INT                  { $$ = newint($1); }
   | IMG NAME '=' img     { $$ = newasgn($2,$4); }                   
   | DOUBLE               { $$ = newdouble($1); }
   | FUNC '(' explist ')' { $$ = newfunc($1, $3); }
   | NAME                 { $$ = newref($1); }
   | NAME '=' exp         { $$ = newasgn($1, $3); }
   | NAME '(' explist ')' { $$ = newcall($1, $3); }
;

img:  PATH  { $$ = newimg($1); } 
;

explist: exp
   | exp ',' explist  { $$ = newast('L', $1, $3); }
;

symlist: NAME         { $$ = newsymlist($1, NULL); }
   | NAME ',' symlist { $$ = newsymlist($1, $3); }
;

program: /* nothing */
   | program stmt {
   if(debug){
      dumpast($2, 0);
   }
   eval($2);
   treefree($2);
   }
    
   | program DEF NAME '(' symlist ')' '{' list '}' {
                       dodef($3, $5, $8);
                       printf("Defined %s\n", $3->name); }

   | program error '\n' { yyerrok; printf("> "); }
;

%%