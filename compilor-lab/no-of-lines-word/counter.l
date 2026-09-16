%{
#include <stdio.h>

int chars = 0, words = 0, lines = 0;
%}

%%

[a-zA-Z0-9]+    { words++; chars += yyleng; }

\n              { lines++; chars++; }

.               { chars++; }

%%

int main(int argc, char *argv[])
{
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            printf("Could not open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }

    yylex();

    printf("Lines    : %d\n", lines);
    printf("Words    : %d\n", words);
    printf("Characters: %d\n", chars);

    return 0;
}

int yywrap()
{
    return 1;
}
