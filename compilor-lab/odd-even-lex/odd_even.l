%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

[0-9]+ {
    int n = atoi(yytext);

    if (n % 2 == 0)
        printf("%d : Even\n", n);
    else
        printf("%d : Odd\n", n);
}

[ \t\n]+ { }

. { }

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