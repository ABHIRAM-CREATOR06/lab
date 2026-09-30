%{
#include <stdio.h>
int digits = 0, letters = 0;
%}

%%

[0-9]      { digits++; }
[a-zA-Z]   { letters++; }
.          { }

%%

int main()
{
    yylex();

    printf("Letters = %d\n", letters);
    printf("Digits = %d\n", digits);

    return 0;
}

int yywrap()
{
    return 1;
}