%{
#include <stdio.h>
int whitespace_count = 0;
int newline_count = 0;
%}

%%

[ ]       { whitespace_count++; }
\n        { newline_count++; }

.         ;  /* Ignore other characters */

%%

int main(int argc, char **argv) {
    yylex();
    printf("Total Whitespaces: %d\n", whitespace_count);
    printf("Total Newlines: %d\n", newline_count);
    return 0;
}

int yywrap() {
    return 1;
}
