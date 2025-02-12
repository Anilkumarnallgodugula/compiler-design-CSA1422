%{
   #include <stdio.h>
%}

%%

 

[ \t\n]+                          { /* Ignore spaces, tabs, and newlines */ }

[0-9]+(\.[0-9]+)?               { printf("Constant: %s\n", yytext); }

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
    return 0;
}

int yywrap() {
    return 1;
}

