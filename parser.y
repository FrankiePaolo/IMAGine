%{
# include <stdio.h>
%}

%token IF

%%
stmt:
| stmt{;}
;

stmt: IF    {printf("Command if");}
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
