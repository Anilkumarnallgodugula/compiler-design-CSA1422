%{
#include <stdio.h>
#include <ctype.h>
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*   { printf("VALID IDENTIFIER: %s\n", yytext); }

[0-9]+                  { printf("INVALID IDENTIFIER (Starts with a digit): %s\n", yytext); }

.                       { printf("INVALID CHARACTER: %s\n", yytext); }

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
