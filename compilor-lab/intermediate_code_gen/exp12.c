#include <stdio.h>
#include <ctype.h>
#include <string.h>

int prec(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int main() {
    char str[50], postfix[50], stack[50];
    char tac[50][10];
    int top = -1, k = 0, t = 1;

    printf("Enter expression (e.g., x=a+b*c): ");
    scanf("%s", str);

    char *eq = strchr(str, '=');
    char target[10] = "";
    char *expr = str;

    if (eq != NULL) {
        *eq = '\0';
        strcpy(target, str);
        expr = eq + 1;
    }

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isalnum(expr[i])) {
            postfix[k++] = expr[i];
        } else {
            while (top != -1 && prec(stack[top]) >= prec(expr[i])) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = expr[i];
        }
    }
    while (top != -1) {
        postfix[k++] = stack[top--];
    }
    postfix[k] = '\0';

    printf("\nIntermediate Code:\n");
    top = -1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            char op[2] = {postfix[i], '\0'};
            strcpy(tac[++top], op);
        } else {
            char op2[10], op1[10], temp[10];
            strcpy(op2, tac[top--]);
            strcpy(op1, tac[top--]);
            sprintf(temp, "t%d", t++);
            printf("%s = %s %c %s\n", temp, op1, postfix[i], op2);
            strcpy(tac[++top], temp);
        }
    }

    if (target[0] != '\0') {
        printf("%s = %s\n", target, tac[top]);
    }

    return 0;
}
