 #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_EXPR_LENGTH 100

// Function to return precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to perform arithmetic operations
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': {
            int result = 1;
            int j;
            for (j = 0; j < b; j++) result *= a;
            return result;
        }
    }
    return 0;
}

// Function to evaluate the expression
int evaluate(char* expr) {
    int values[MAX_EXPR_LENGTH], val_top = -1;
    char ops[MAX_EXPR_LENGTH];
    int op_top = -1;
    int i;
    int len = strlen(expr);

    for (i = 0; i < len; i++) {
        if (expr[i] == ' ') continue;

        if (isdigit(expr[i])) {
            int val = 0;
            while (i < len && isdigit(expr[i])) {
                val = (val * 10) + (expr[i] - '0');
                i++;
            }
            i--;
            val_top++;
            values[val_top] = val;
        }
        else if (expr[i] == '(') {
            op_top++;
            ops[op_top] = expr[i];
        }
        else if (expr[i] == ')') {
            while (op_top != -1 && ops[op_top] != '(') {
                int b = values[val_top--];
                int a = values[val_top--];
                char op = ops[op_top--];
                val_top++;
                values[val_top] = applyOp(a, b, op);
            }
            op_top--; // Remove '('
        }
        else {
            while (op_top != -1 && precedence(ops[op_top]) >= precedence(expr[i])) {
                int b = values[val_top--];
                int a = values[val_top--];
                char op = ops[op_top--];
                val_top++;
                values[val_top] = applyOp(a, b, op);
            }
            op_top++;
            ops[op_top] = expr[i];
        }
    }

    while (op_top != -1) {
        int b = values[val_top--];
        int a = values[val_top--];
        char op = ops[op_top--];
        val_top++;
        values[val_top] = applyOp(a, b, op);
    }

    return values[val_top];
}

int main() {
    char expr[MAX_EXPR_LENGTH];

    printf("Enter an expression to evaluate (using PEMDAS rules): ");
    fgets(expr, MAX_EXPR_LENGTH, stdin);
    expr[strcspn(expr, "\n")] = '\0';

    int result = evaluate(expr);
    printf("The result of the expression is: %d\n", result);

    return 0;
}

