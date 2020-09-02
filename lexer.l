/* recognize tokens */

%option noyywrap nodefault yylineno
%{
# include "utils.h"
# include "builtin.h"
# include "parser.tab.h"
%}

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
"{" |
"}" |
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
"def"   { return DEF; }
"img"   { return IMG; }
"list"  { return LIST; }
 
 /* built in functions */
"print" { yylval.fn = B_print; return FUNC; }
"width" { yylval.fn = I_width; return FUNC; }
"invert" { yylval.fn = I_invert; return FUNC; }
"average" { yylval.fn = I_average; return FUNC; }
"print_list" { yylval.fn=return PRLIST}


 /* debug hack */
"debug"[0-9]+ { debug = atoi(&yytext[5]); printf("debug set to %d\n", debug); }

 /* names */
[a-zA-Z][a-zA-Z0-9]*  { yylval.s = lookup(yytext); return NAME; }

 /* path */
#{1}.+(png|jpeg|jpg|bpm) { yylval.path=(yytext); return PATH; }

 /* int */
\-?[0-9]+                { yylval.i = atoi(yytext); return INT; }

 /* double */
\-?[0-9]+\.{1}[0-9]+     { yylval.d = atof(yytext); return DOUBLE; }


"//".*  
[ \t]   /* ignore white space */ 
\\\n    printf("> "); /* ignore line continuation */
"\n"    printf("> ");

.	    { yyerror("Unknown character %c\n", *yytext); }
%%
