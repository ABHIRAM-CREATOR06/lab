%{
#include <stdio.h>
#include <math.h>

int yylex();
int yyerror(char *s);
%}

%token NUM PLUS MINUS MUL DIV POW LPAREN RPAREN NEWLINE

%left PLUS MINUS
%left MUL DIV
%right POW

%%

program:
    program line
    | line
    ;

line:
    expr NEWLINE   { printf("Result = %.2f\n", $1); }
    | NEWLINE
    ;

expr:
    expr PLUS expr    { $$ = $1 + $3; }
    | expr MINUS expr { $$ = $1 - $3; }
    | expr MUL expr   { $$ = $1 * $3; }
    | expr DIV expr   {
                          if ($3 == 0) {
                              printf("Error: Division by zero\n");
                              $$ = 0;
                          } else {
                              $$ = $1 / $3;
                          }
                      }
    | expr POW expr   { $$ = pow($1, $3); }
    | MINUS expr %prec MINUS { $$ = -$2; }
    | LPAREN expr RPAREN     { $$ = $2; }
    | NUM             { $$ = $1; }
    ;

%%

int yyerror(char *s)
{
    printf("Error: %s\n", s);
    return 0;
}

int main()
{
    printf("Enter expression, Ctrl+D to exit:\n");
    yyparse();
    return 0;
}
