#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char keywords[9][10] = {"int","float","if","else","while","for","return","char","void"};

bool isEnd(char ch) {
    return (ch==' '||ch=='+'||ch=='-'||ch=='*'||ch=='/'||
            ch==';'||ch=='('||ch==')'||ch=='='||ch=='<'||ch=='>');
}

bool isOperator(char ch) {
    return (ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='='||ch=='<'||ch=='>');
}

bool isPunct(char ch) {
    return (ch==';'||ch=='('||ch==')');
}

bool isKeyword(char token[]) {
    int i;
    for (i = 0; i < 9; i++)
        if (strcmp(token, keywords[i]) == 0)
            return true;
    return false;
}

bool isDigit(char token[]) {
    int i;
    for (i = 0; token[i] != '\0'; i++)
        if (token[i] < '0' || token[i] > '9')
            return false;
    return true;
}

bool isIdentifier(char token[]) {
    if (token[0] >= '0' && token[0] <= '9')
        return false;
    return true;
}

void parse(char str[]) {
    int left = 0, right = 0;
    int len = strlen(str);
    char token[100];
    int i, j;

    while (right <= len) {
        if (!isEnd(str[right])) {
            right++;
            continue;
        }

        if (left == right) {
            if (isOperator(str[right]))
                printf("'%c' is an OPERATOR\n", str[right]);
            else if (isPunct(str[right]))
                printf("'%c' is a PUNCTUATION\n", str[right]);
            right++;
            left = right;
        } else {
            j = 0;
            for (i = left; i <= right - 1; i++)
                token[j++] = str[i];
            token[j] = '\0';

            if (isKeyword(token))
                printf("'%s' is a KEYWORD\n", token);
            else if (isDigit(token))
                printf("'%s' is a NUMBER\n", token);
            else if (isIdentifier(token))
                printf("'%s' is an IDENTIFIER\n", token);
            else
                printf("'%s' is INVALID\n", token);

            left = right;
        }
    }
}

int main() {
    char str[100];

    printf("Enter an expression to analyze: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';

        printf("\nAnalyzing: %s\n", str);
        parse(str);
    }

    return 0;
}
