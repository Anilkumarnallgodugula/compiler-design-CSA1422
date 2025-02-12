#include <stdio.h>
#include <string.h>

void eliminate_left_factoring(char* non_terminal, char productions[][50], int num_productions) {
    int i, j, prefix_len = 0;
    char prefix[50];
    
    // Find common prefix
    strcpy(prefix, productions[0]);
    for (i = 1; i < num_productions; i++) {
        j = 0;
        while (productions[i][j] == prefix[j] && productions[i][j] != '\0') {
            j++;
        }
        prefix[j] = '\0';
    }

    prefix_len = strlen(prefix);

    if (prefix_len == 0) {
        printf("No left factoring needed.\n");
        return;
    }

    // Display factored productions
    printf("%s -> %s%s'\n", non_terminal, prefix, non_terminal);
    printf("%s' ->", non_terminal);
    for (i = 0; i < num_productions; i++) {
        if (strlen(productions[i]) == prefix_len) {
            printf(" e");
        } else {
            printf(" %s", productions[i] + prefix_len);
        }
        if (i != num_productions - 1) printf(" | ");
    }
    printf("\n");
}

int main() {
    char non_terminal[10];
    int num_productions;
    char productions[10][50];
    int i;

    printf("Enter the non-terminal: ");
    scanf("%s", non_terminal);
    printf("Enter the number of productions: ");
    scanf("%d", &num_productions);
    getchar();  // Consume newline character

    printf("Enter the productions (one per line):\n");
    for (i = 0; i < num_productions; i++) {
        fgets(productions[i], sizeof(productions[i]), stdin);
        productions[i][strcspn(productions[i], "\n")] = '\0';  // Remove newline
    }

    eliminate_left_factoring(non_terminal, productions, num_productions);

    return 0;
}

