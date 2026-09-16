%{
#include <stdio.h>
%}

%%

"#include"[ \t]*"<"[a-zA-Z0-9_./]*">"   { printf("%s : Header File\n", yytext); }

"int"|"float"|"char"|"while"|"if"|"double"|"for"|"do"|"goto"|"void"   { printf("%s : Keyword\n", yytext); }

[0-9]+                                  { printf("%s : Digit\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*                  { printf("%s : Identifier\n", yytext); }

"+"|"-"|"*"|"/"                         { printf("%s : Operator\n", yytext); }

"."                                     { /* skip */ }

[ \t\n]+                                { /* skip whitespace */ }

.                                       { /* skip anything else */ }

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

    if (argc > 1)
        fclose(yyin);

    return 0;
}

int yywrap()
{
    return 1;
}
