 #include <stdio.h>
#include <string.h>

void eliminate_left_recursion(char* non_terminal, char productions[][50], int num_productions) {
    char alpha[10][50], beta[10][50];
    int alpha_count = 0, beta_count = 0;
    int i;

    for (i = 0; i < num_productions; i++) {
        if (productions[i][0] == non_terminal[0]) {
            strcpy(alpha[alpha_count], productions[i] + 1);
            alpha_count++;
        } else {
            strcpy(beta[beta_count], productions[i]);
            beta_count++;
        }
    }

    if (alpha_count == 0) {
        printf("No left recursion detected.\n");
        return;
    }

    printf("%s ->", non_terminal);
    for (i = 0; i < beta_count; i++) {
        printf(" %s%s'", beta[i], non_terminal);
        if (i != beta_count - 1) printf(" | ");
    }
    printf("\n");

    printf("%s' ->", non_terminal);
    for (i = 0; i < alpha_count; i++) {
        printf(" %s%s'", alpha[i], non_terminal);
        if (i != alpha_count - 1) printf(" | ");
    }
    printf(" | e\n");
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

    eliminate_left_recursion(non_terminal, productions, num_productions);

    return 0;
}

