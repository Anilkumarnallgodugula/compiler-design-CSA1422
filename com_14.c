 #include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

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

    eliminate_common_subexpressions(code, line_count);

    return 0;
}

