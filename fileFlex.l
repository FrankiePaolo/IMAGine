%{
    # include "parser.tab.h"
%}

%% 
if                                  { return IF;}
.+\.(png|jpg|jpeg)                  { yylval.str = strdup(yytext);return PATH;}
\n                                  { return EOL;}
%%