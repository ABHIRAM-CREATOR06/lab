#include <stdio.h>
#include <string.h>

struct quad {
    char op[10], arg1[10], arg2[10], res[10];
} c[20];

int main() {
    int n;

    printf("Enter number of quadruples: ");
    scanf("%d", &n);

    printf("Enter quadruples (op arg1 arg2 res):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %s %s %s", c[i].op, c[i].arg1, c[i].arg2, c[i].res);
    }

    printf("\nTarget Assembly Code:\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(c[i].op, "+") == 0) {
            printf("MOV R0, %s\nADD R0, %s\nMOV %s, R0\n", c[i].arg1, c[i].arg2, c[i].res);
        } else if (strcmp(c[i].op, "-") == 0) {
            printf("MOV R0, %s\nSUB R0, %s\nMOV %s, R0\n", c[i].arg1, c[i].arg2, c[i].res);
        } else if (strcmp(c[i].op, "*") == 0) {
            printf("MOV R0, %s\nMUL R0, %s\nMOV %s, R0\n", c[i].arg1, c[i].arg2, c[i].res);
        } else if (strcmp(c[i].op, "/") == 0) {
            printf("MOV R0, %s\nDIV R0, %s\nMOV %s, R0\n", c[i].arg1, c[i].arg2, c[i].res);
        } else if (strcmp(c[i].op, "=") == 0) {
            printf("MOV R0, %s\nMOV %s, R0\n", c[i].arg1, c[i].res);
        }
    }

    return 0;
}
