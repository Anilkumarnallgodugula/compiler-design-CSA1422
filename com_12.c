#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

char input[MAX], postfix[MAX], stack[MAX];
int top = -1, tempVar = 1;

// Function to check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to convert infix expression to postfix
void infixToPostfix() {
    int i = 0, j = 0;
    char ch;
    
    while ((ch = input[i++]) != '\0') {
        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            stack[++top] = ch;
        } else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            top--;  // Pop '('
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = ch;
        }
    }
    while (top != -1) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';
}

// Function to generate Three Address Code from postfix expression
void generateTAC() {
    char operand1[5], operand2[5], result[5];
    int i = 0;
    char ch;
    
    printf("\nThree Address Code:\n");
    while ((ch = postfix[i++]) != '\0') {
        if (isalnum(ch)) {
            // Push operands to stack
            char temp[2] = {ch, '\0'};
            stack[++top] = ch;
        } else {
            // Pop two operands for the operation
            char op2 = stack[top--];
            char op1 = stack[top--];
            
            sprintf(result, "t%d", tempVar++);
            
            printf("%s = %c %c %c\n", result, op1, ch, op2);
            
            // Push the result back to stack
            stack[++top] = result[0];
        }
    }
    // Final result assignment
    printf("Result = t%d\n", tempVar - 1);
}

int main() {
    printf("Enter an arithmetic expression: ");
    scanf("%s", input);
    
    infixToPostfix();
    printf("Postfix Expression: %s\n", postfix);
    
    generateTAC();
    
    return 0;
}

