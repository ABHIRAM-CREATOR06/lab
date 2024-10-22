#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack variables
int top = -1;
char stack[MAX];

// Function to push an element to the stack
void push(char ch) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = ch;
}

// Function to pop an element from the stack
char pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack[top--];
}

// Function to check the precedence of operators
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

// Function to convert infix expression to postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i = 0, k = 0;
    char ch;
    
    while ((ch = infix[i++]) != '\0') {
        if (isdigit(ch) || isalpha(ch)) {
            postfix[k++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
            }
            pop();  // Remove '(' from stack
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[k++] = pop();
            }
            push(ch);
        }
    }
    
    while (top != -1) {
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
}
void menu() {
    printf("Menu:\n");
    printf("1. Convert Infix to Postfix\n");
    printf("2. Exit\n");
}

int main() {
    char infix[MAX], postfix[MAX];
    int choice;
    
    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;
            case 2:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

