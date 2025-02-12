 #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

// Structure to represent intermediate code
typedef struct {
    char operation[10];
    char arg1[20];
    char arg2[20];
    char result[20];
} IntermediateCode;

// Lexical Analyzer to identify tokens
void lexical_analyzer(char code[MAX_LINES][MAX_LENGTH], int line_count) {
    printf("\nLexical Analysis:\n");
    int i;
    for (i = 0; i < line_count; i++) {
        char line[MAX_LENGTH];
        strcpy(line, code[i]);
        char *token = strtok(line, " \t");
        while (token != NULL) {
            if (isalpha(token[0]) || token[0] == '_') {
                printf("Identifier: %s\n", token);
            } else if (isdigit(token[0])) {
                printf("Constant: %s\n", token);
            } else if (strchr("+-*/=", token[0])) {
                printf("Operator: %s\n", token);
            }
            token = strtok(NULL, " \t");
        }
    }
}

// Syntax Analyzer to check basic syntax
int syntax_analyzer(char code[MAX_LINES][MAX_LENGTH], int line_count) {
    printf("\nSyntax Analysis:\n");
    int i;
    for (i = 0; i < line_count; i++) {
        if (strchr(code[i], '=') == NULL) {
            printf("Syntax Error in line %d: Missing '='\n", i + 1);
            return 0;
        }
    }
    printf("Syntax is correct.\n");
    return 1;
}

// Semantic Analyzer for basic checks
int semantic_analyzer(char code[MAX_LINES][MAX_LENGTH], int line_count) {
    printf("\nSemantic Analysis:\n");
    int i;
    for (i = 0; i < line_count; i++) {
        if (isdigit(code[i][0])) {
            printf("Semantic Error in line %d: Variable name cannot start with a digit.\n", i + 1);
            return 0;
        }
    }
    printf("Semantics are correct.\n");
    return 1;
}

// Function to generate intermediate code
void generate_intermediate_code(IntermediateCode code[], int count) {
    printf("\nIntermediate Code:\n");
    int i;
    for (i = 0; i < count; i++) {
        printf("%s = %s %s %s\n", code[i].result, code[i].arg1, code[i].operation, code[i].arg2);
    }
}

// Function to generate assembly code from intermediate code
void generate_assembly(IntermediateCode code[], int count) {
    printf("\nGenerated Assembly Code:\n");
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(code[i].operation, "+") == 0) {
            printf("MOV R0, %s\n", code[i].arg1);
            printf("ADD R0, %s\n", code[i].arg2);
            printf("MOV %s, R0\n", code[i].result);
        } else if (strcmp(code[i].operation, "-") == 0) {
            printf("MOV R0, %s\n", code[i].arg1);
            printf("SUB R0, %s\n", code[i].arg2);
            printf("MOV %s, R0\n", code[i].result);
        } else if (strcmp(code[i].operation, "*") == 0) {
            printf("MOV R0, %s\n", code[i].arg1);
            printf("MUL R0, %s\n", code[i].arg2);
            printf("MOV %s, R0\n", code[i].result);
        } else if (strcmp(code[i].operation, "/") == 0) {
            printf("MOV R0, %s\n", code[i].arg1);
            printf("DIV R0, %s\n", code[i].arg2);
            printf("MOV %s, R0\n", code[i].result);
        }
    }
}

// Function to eliminate common subexpressions
void eliminate_common_subexpressions(char code[MAX_LINES][MAX_LENGTH], int line_count) {
    char optimized_code[MAX_LINES][MAX_LENGTH];
    int optimized_index = 0;
    int i, j;

    for (i = 0; i < line_count; i++) {
        int is_common = 0;
        for (j = 0; j < i; j++) {
            if (strcmp(code[i], code[j]) == 0) {
                is_common = 1;
                break;
            }
        }

        if (!is_common) {
            strcpy(optimized_code[optimized_index++], code[i]);
        }
    }

    printf("\nOptimized Code:\n");
    for (i = 0; i < optimized_index; i++) {
        printf("%s\n", optimized_code[i]);
    }

    // Convert optimized code to intermediate code format
    IntermediateCode intermediate[MAX_LINES];
    int intermediate_count = 0;
    for (i = 0; i < optimized_index; i++) {
        sscanf(optimized_code[i], "%s = %s %s %s", intermediate[intermediate_count].result, 
               intermediate[intermediate_count].arg1, intermediate[intermediate_count].operation, 
               intermediate[intermediate_count].arg2);
        intermediate_count++;
    }

    generate_intermediate_code(intermediate, intermediate_count);
    generate_assembly(intermediate, intermediate_count);
}

int main() {
    int line_count;
    char code[MAX_LINES][MAX_LENGTH];
    int i;

    printf("Enter the number of lines of code: ");
    scanf("%d", &line_count);
    getchar(); // To consume the newline character after scanf

    printf("Enter the code line by line:\n");
    for (i = 0; i < line_count; i++) {
        fgets(code[i], MAX_LENGTH, stdin);
        code[i][strcspn(code[i], "\n")] = '\0';  // Remove newline character
    }

    lexical_analyzer(code, line_count);
    if (syntax_analyzer(code, line_count) && semantic_analyzer(code, line_count)) {
        eliminate_common_subexpressions(code, line_count);
    } else {
        printf("\nCompilation halted due to errors.\n");
    }

    return 0;
}

