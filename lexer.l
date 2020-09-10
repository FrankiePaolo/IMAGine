/* recognize tokens */

%option noyywrap nodefault yylineno

%{
# include <string.h>
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
":" |
")"     { return yytext[0]; }

 /* comparison ops */
">"     { yylval.fn = 1; return CMP; }
"<"     { yylval.fn = 2; return CMP; }
"!="    { yylval.fn = 3; return CMP; }
"=="    { yylval.fn = 4; return CMP; }
">="    { yylval.fn = 5; return CMP; }
"<="    { yylval.fn = 6; return CMP; }

 /* keywords */

"if"    { return IF; }
"then"  { return THEN; }
"else"  { return ELSE; }
"while" { return WHILE; }
"do"    { return DO; }
"foreach" { return FOREACH; }
"def"   { return DEF; }
"img"   { return IMG; }
"list"  { return LIST; }
"&&"    { return AND; }
"||"    { return OR;}
 
 /* built in functions */
"print" { yylval.fn = b_print; return FUNC; }
"width" { yylval.fn = b_width; return FUNC; }
"height" { yylval.fn = b_height; return FUNC; }
"bands" { yylval.fn = b_bands; return FUNC; }
"crop"   { yylval.fn = b_crop; return FUNC; }
"smartCrop" { yylval.fn = b_smartcrop; return FUNC; }
"add"   { yylval.fn = b_add; return FUNC; }
"subtract"   { yylval.fn = b_subtract; return FUNC; }
"invert" { yylval.fn = b_invert; return FUNC; }
"average" { yylval.fn = b_average; return FUNC; }
"min" { yylval.fn = b_min; return FUNC; }
"max" { yylval.fn = b_max; return FUNC; }
"push"    { yylval.fn = b_push; return FUNC; }
"pop"    { yylval.fn = b_pop; return FUNC; }
"insert"    { yylval.fn = b_insert; return FUNC; }
"remove"    { yylval.fn = b_remove; return FUNC; }
"get"    { yylval.fn = b_get; return FUNC; }
"length"    { yylval.fn = b_length; return FUNC; }
"convertColorSpace" { yylval.fn = b_convert; return FUNC; }
"rotate" { yylval.fn = b_rotate; return FUNC; }
"histEq" { yylval.fn = b_histeq; return FUNC; }
"normalise" { yylval.fn = b_histeq; return FUNC; }
"gaussianBlur" { yylval.fn = b_gaussianblur; return FUNC; }
"canny" { yylval.fn = b_canny; return FUNC; }
"sobel" { yylval.fn = b_sobel; return FUNC; }
"flip" { yylval.fn = b_flip; return FUNC; }
"sharpen" { yylval.fn = b_sharpen; return FUNC; }
"zoom" { yylval.fn = b_zoom; return FUNC; }
"convert" { yylval.fn = b_copyfile; return FUNC; }

 /* debug hack */
"debug"[0-9]+ { debug = atoi(&yytext[5]); printf("debug set to %d\n", debug); }

 /* names */
[a-zA-Z][a-zA-Z0-9]*  { yylval.s = lookup(yytext); return NAME; }

 /* string */
\"{1}.[^"]*\"{1}       { yytext++;yylval.str=(yytext);return STRING; } 

 /* int */
[0-9]+                { yylval.i = atoi(yytext); return INT; }

 /* double */
[0-9]+\.{1}[0-9]+     { yylval.d = atof(yytext); return DOUBLE; }


"//".*  
[ \t]   /* ignore white space */ 
\\\n    /* ignore line continuation */
"\n"    

.	    { yyerror("Unknown character %c\n", *yytext); }
%%
