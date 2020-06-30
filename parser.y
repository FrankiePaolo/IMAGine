%{
# include <stdio.h>
# include <vips/vips.h>
%}

%token IF

%%
stmt:
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
