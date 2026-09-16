%{
#include <stdio.h>
#include <stdlib.h>

int op = 0;
float a, b;

void eval();
%}

%%

[0-9]*"."[0-9]+|[0-9]+   { eval(); }

"+"     { op = 1; }
"-"     { op = 2; }
"*"     { op = 3; }
"/"     { op = 4; }
"^"     { op = 5; }

"\n"    { printf("Result = %.2f\n", a); }

[ \t]   { /* skip spaces */ }

.       { /* skip unknown characters */ }

%%

void eval()
{
    if (op == 0) {
        a = atof(yytext);
    } else {
        b = atof(yytext);
        int i;
        switch (op) {
            case 1: a = a + b; break;
            case 2: a = a - b; break;
            case 3: a = a * b; break;
            case 4: a = a / b; break;
            case 5:
                i = (int)a;
                float base = a;
                while (b > 1) {
                    a = a * base;
                    b--;
                }
                break;
        }
        op = 0;
    }
}

int main()
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
