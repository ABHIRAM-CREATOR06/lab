%{
#include <stdio.h>
int v=0, c=0;
%}

%%

[aeiouAEIOU]   { v++; }
[a-zA-Z]       { c++; }
.              { }

%%

int main()
{
    yylex();

    printf("Vowels = %d\n", v);
    printf("Consonants = %d\n", c);

    return 0;
}

int yywrap()
{
    return 1;
}