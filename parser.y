%{
# include <stdio.h>
%}

%token NUMERO
%token SOMMA SOTTRAZIONE PRODOTTO DIVISIONE VAL_ASSOLUTO
%token OP CP
%token EOL


%%
calclist: /* niente */
| calclist exp EOL { printf("=%d\n>",$2);}
| calclist EOL { printf(">"); } /* linea vuota o commento */
;

exp: factor
| exp SOMMA exp {$$ = $1 + $3;}
| exp SOTTRAZIONE factor {$$ = $1 - $3;}
| exp VAL_ASSOLUTO factor {$$ = $1 | $3;}
;

factor: term
| factor PRODOTTO term {$$ = $1 * $3;}
| factor DIVISIONE term {$$ = $1 / $3;}
;

term: NUMERO
| VAL_ASSOLUTO term {$$ = $2 >=0? $2: -$2;}
| OP exp CP { $$ = $2;}
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
