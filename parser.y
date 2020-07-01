%{
# include <stdio.h>
# include <vips/vips.h>
%}

%union {
    char * str;
}

%token IF
%token EOL
%token <str> PATH
%start flow
%type <str> expr

%%
flow:   /* it starts here */
    | flow expr EOL         { printf("%s\n",$2); } 
    | flow EOL              {;}
;

expr: 
;
%%

int main(int argc, char** argv) {
    printf(">");
    yyparse();
    return 0;
}

yyerror(char *s){
    fprintf(stderr, "error: %s\n", s);
}
