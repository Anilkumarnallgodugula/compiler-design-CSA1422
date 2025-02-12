 %{
#include <stdio.h>
int char_count = 0;
int line_count = 0;
int word_count = 0;
%}

%%

/\*([^*]|\*+[^*/])*\*+/        ; /* Ignore multi-line comments */
//[^
]*                         ; /* Ignore single-line comments */

[ \t]+                         ; /* Ignore redundant spaces and tabs */
\n                             { line_count++; char_count++; }

[a-zA-Z_][a-zA-Z0-9_]*         { word_count++; char_count += yyleng; }

[0-9]+                         { word_count++; char_count += yyleng; }

.                              { char_count += yyleng; }

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <input_file.c>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    yyin = file;
    yylex();
    fclose(file);

    printf("Total Characters: %d\n", char_count);
    printf("Total Words: %d\n", word_count);
    printf("Total Lines: %d\n", line_count);
    return 0;
}

int yywrap() {
    return 1;
}

