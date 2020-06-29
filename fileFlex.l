%{
    # include "parser.tab.h"
%}

%%
"+" { return SOMMA;}
"-" { return SOTTRAZIONE;}
"*" {return PRODOTTO; }
"/" {return DIVISIONE;}
"|" {return VAL_ASSOLUTO; }
"(" {return OP;}
")" { return CP; }
[0-9]+ { yylval = atoi(yytext); return NUMERO; }

\n { return EOL; }
"//".*
[ \t] { /*ignora spazi bianchi */ }
. { yyerror("Carattere misterioso %c \n", *yytext);}
%%