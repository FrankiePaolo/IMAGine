/* recognize tokens for the calculator */

%option noyywrap nodefault yylineno
%{
# include "advanced_calc.h"
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
"let"   { return LET;}
"num"   { return NUM; }
"img"   { return IMG; }

 /* debug hack */
"debug"[0-9]+ { debug = atoi(&yytext[5]); printf("debug set to %d\n", debug); }

 /* names */
.+\.(png|jpg|jpeg)    { yylval.s = lookup(yytext); return PATH; }
[a-zA-Z][a-zA-Z0-9]*  { yylval.s = lookup(yytext); return NAME; }

.+\.(png|jpg|jpeg)    {yylval.p=yytext; return PATH; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }

"//".*  
[ \t]   /* ignore white space */ 
\\\n    printf("c> "); /* ignore line continuation */
"\n"    { return EOL; }

.	{ yyerror("Mystery character %c\n", *yytext); }
%%
