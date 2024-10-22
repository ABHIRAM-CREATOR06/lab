#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

int stack[MAX];
int top = -1;

// Function to push an element to the stack
void push(int value) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = value;
}

// Function to pop an element from the stack
int pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

// Function to evaluate a postfix expression
int evaluatePostfix(char* exp) {
    int i;
    for (i = 0; exp[i]; ++i) {
        if (isdigit(exp[i])) {
            push(exp[i] - '0'); // Convert char to int
        } else {
            int val1 = pop();
            int val2 = pop();
            switch (exp[i]) {
                case '+': push(val2 + val1); break;
                case '-': push(val2 - val1); break;
                case '*': push(val2 * val1); break;
                case '/': push(val2 / val1); break;
                case '^': push(pow(val2, val1)); break;
                default: printf("Invalid operator\n"); exit(1);
            }
        }
    }
    return pop();
}

int main() {
    char exp[MAX];
    printf("Enter postfix expression: ");
    scanf("%s", exp);
    printf("Postfix evaluation result: %d\n", evaluatePostfix(exp));
    return 0;
}
