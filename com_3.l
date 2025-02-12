 %{
#include <stdio.h>
%}

%%
\+        { printf("PLUS\n"); }
-         { printf("MINUS\n"); }
\*        { printf("MULTIPLY\n"); }
/         { printf("DIVIDE\n"); }

.         { printf("INVALID CHARACTER: %s\n", yytext); }

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

