/* recognize tokens for the calculator */

%option noyywrap nodefault yylineno
%{
# include "utils.h"
# include "parser.tab.h"
%}

/* float exponent */
EXP	([Ee][-+]?[0-9]+)

%%
 /* single character ops */
"+" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
";" |
"(" |
")"     { return yytext[0]; }

 /* comparison ops */
">"     { yylval.fn = 1; return CMP; }
"<"     { yylval.fn = 2; return CMP; }
"<>"    { yylval.fn = 3; return CMP; }
"=="    { yylval.fn = 4; return CMP; }
">="    { yylval.fn = 5; return CMP; }
"<="    { yylval.fn = 6; return CMP; }

 /* keywords */

"if"    { return IF; }
"then"  { return THEN; }
"else"  { return ELSE; }
"while" { return WHILE; }
"do"    { return DO; }
"def"   { return DEF;}
"num"   { return NUM; }
"img"   { return IMG; }

 /* debug hack */
"debug"[0-9]+ { debug = atoi(&yytext[5]); printf("debug set to %d\n", debug); }

 /* strings */
[a-zA-Z][a-zA-Z0-9]*  { yylval.s = lookup(yytext); return STRING; }

.+\.(png|jpg|jpeg)    {yylval.s=lookup(yytext); return PATH; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.i = atof(yytext); return INT; }

"//".*  
[ \t]   /* ignore white space */ 
\\\n    printf("c> "); /* ignore line continuation */
"\n"    {  }

.	{ yyerror("Mystery character %c\n", *yytext); }
%%
