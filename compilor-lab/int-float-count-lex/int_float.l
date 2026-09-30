%{
#include <stdio.h>
%}

%%

[0-9]+              { printf("%s : Integer\n", yytext); }

[0-9]+\.[0-9]+      { printf("%s : Float\n", yytext); }

[ \t\n]+            { }

.                   { }

%%

int main()
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}