 #include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IDENTIFIER_LENGTH 31
#define MAX_TOKEN_LENGTH 100

void remove_comments(char* code) {
    int i = 0, j = 0;
    while (code[i]) {
        if (code[i] == '/' && code[i+1] == '/') {
            while (code[i] && code[i] != '\n') i++;
        } else if (code[i] == '/' && code[i+1] == '*') {
            i += 2;
            while (code[i] && !(code[i] == '*' && code[i+1] == '/')) i++;
            i += 2;
        } else {
            code[j++] = code[i++];
        }
    }
    code[j] = '\0';
}

void lexical_analyzer(char* code) {
    int i = 0;
    char token[MAX_TOKEN_LENGTH];

    while (code[i] != '\0') {
        if (isspace(code[i])) {
            i++;
            continue;
        }

        if (isalpha(code[i]) || code[i] == '_') {  // Identifiers
            int len = 0;
            while (isalnum(code[i]) || code[i] == '_') {
                if (len < MAX_IDENTIFIER_LENGTH) {
                    token[len++] = code[i];
                }
                i++;
            }
            token[len] = '\0';
            printf("Identifier: %s\n", token);
        }
        else if (isdigit(code[i])) {  // Constants
            int len = 0;
            while (isdigit(code[i])) {
                token[len++] = code[i++];
            }
            token[len] = '\0';
            printf("Constant: %s\n", token);
        }
        else {  // Operators and others
            if (strchr("+-*/%=<>&|!^", code[i])) {
                printf("Operator: %c\n", code[i]);
                i++;
            } else {
                i++;  // Ignore unknown characters
            }
        }
    }
}

int main() {
    FILE *file;
    char filename[100];
    char *code;
    long file_size;

    printf("Enter the filename: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    code = (char *)malloc(file_size + 1);
    if (code == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    fread(code, 1, file_size, file);
    code[file_size] = '\0';

    fclose(file);

    remove_comments(code);
    lexical_analyzer(code);

    free(code);
    return 0;
}

