%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+"."[0-9]+ |
[0-9]+          { yylval = atof(yytext); return NUM; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }
"^"             { return POW; }
"("             { return LPAREN; }
")"             { return RPAREN; }
\n              { return NEWLINE; }
[ \t]           { /* skip spaces */ }
.               { /* skip unknown */ }

%%

int yywrap()
{
    return 1;
}
