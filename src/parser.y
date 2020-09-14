%{
#include <stdio.h>
#include <stdlib.h>
#include <vips/vips.h>
#include "utils.h"
#include "builtin.h"
#include "eval.h"
%} 


%union {
  struct ast *a;
  int i;
  double d;
  char * str;
  struct symbol *s;		/* symbol */
  struct symlist *sl;
  int fn;			      /* function */
}

/* declare tokens */
%token <i> INT
%token <d> DOUBLE
%token <str> STRING
%token <s> NAME
%token <fn> FUNC
%token EOL

%token IF THEN ELSE WHILE DO DEF IMG LIST FOREACH HELP

%left AND OR
%nonassoc <fn> CMP CND 
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp stmt explist img list value elements foreach name
%type <sl> symlist

%start program

%%

stmt: IF '(' exp ')' THEN '{' list '}' ';'                  { $$ = newflow('I', $3, $7, NULL); }
   | IF '(' exp ')' THEN '{' list '}' ELSE '{' list '}'     { $$ = newflow('I', $3, $7, $11); }
   | WHILE '(' exp ')' DO '{' list '}'                      { $$ = newflow('W', $3, $7, NULL); }
   | FOREACH '(' foreach ')' '{' list '}'                   { $$ = newflow('E', $3, $6, NULL); }
   | exp ';'
;

list:                                                       { $$ = NULL; }
   | stmt  list                                             {  if($2 == NULL){
                                                                  $$ = $1;
                                                               }else{
                                                                  $$ = newast('L', $1, $2);
                                                               }
                                                            }
;

exp: exp AND exp                                            { $$ = newast('&', $1,$3); }
   | exp OR exp                                             { $$ = newast('O', $1,$3); }
   | exp CMP exp                                            { $$ = newcmp($2,  $1,$3); }
   | exp '+' exp                                            { $$ = newast('+', $1,$3); }
   | exp '-' exp                                            { $$ = newast('-', $1,$3); }
   | exp '*' exp                                            { $$ = newast('*', $1,$3); }
   | exp '/' exp                                            { $$ = newast('/', $1,$3); }
   | '|' exp '|'                                            { $$ = newast('|', $2, NULL); }
   | '(' exp ')'                                            { $$ = $2; }
   | FUNC '(' explist ')'                                   { $$ = newfunc($1, $3); }
   | NAME '=' exp                                           { $$ = newasgn($1, $3); }
   | IMG NAME '=' img                                       { $$ = newasgn($2, $4); }  
   | NAME '(' explist ')'                                   { $$ = newcall($1, $3); }
   | value                                                  { $$ = $1; }
;

foreach:    name ':' name                                   { $$ = newast('L', $1, $3); }
;

name: NAME                                                  { $$ = newref($1); }
;

value:  '-' INT %prec UMINUS                                { $$ = newint($2,'-'); }
   | INT                                                    { $$ = newint($1,'+'); }
   | '-' DOUBLE %prec UMINUS                                { $$ = newdouble($2,'-'); } 
   | DOUBLE                                                 { $$ = newdouble($1,'+'); }
   | STRING                                                 { $$ = newstring($1); }
   | NAME                                                   { $$ = newref($1); }
;

img:  STRING                                                { $$ = newimg($1); }
   | FUNC '(' explist ')'                                   { $$ = newfunc($1, $3); }
;

explist: exp          
   | exp ',' explist                                        { $$ = newast('L', $1, $3); }
;

symlist: NAME                                               { $$ = newsymlist($1, NULL); }
   | NAME ',' symlist                                       { $$ = newsymlist($1, $3); }
;

elements:                                                   { $$ = NULL; }
   | value                                                  { $$ = newlist($1,NULL); }    
   | value ',' elements                                     { $$ = newlist($1, $3); }
;

program: /* nothing */
   | HELP                                                   { printHelp(); }
   | program stmt                                           {  if(debug){
                                                                  dumpast($2, 0);
                                                               }
                                                               eval($2);
                                                               treefree($2);
                                                            }
   | program DEF NAME '(' symlist ')' '{' list '}'          { dodef($3, $5, $8); }
   | program LIST NAME '=''{' elements '}' ';'              { dolist($3, $6); }
   | program error '\n'                                     { yyerrok; printf("> "); }
;

%%