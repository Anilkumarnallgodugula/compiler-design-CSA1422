%{
#include <stdio.h>
int macro_count = 0;
int header_count = 0;
%}

%%
 

^#define[ 	]+.*                  { macro_count++; }
^#include[ 	]+<[^>]+>            { header_count++; }
^#include[ 	]+"[^"]+"           { header_count++; }

[ \t\n]+                          { /* Ignore spaces, tabs, and newlines */ }

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

    printf("Total Macros Defined: %d\n", macro_count);
    printf("Total Header Files Included: %d\n", header_count);
    return 0;
}

int yywrap() {
    return 1;
}
