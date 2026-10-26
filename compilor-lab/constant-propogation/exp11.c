#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct quad {
    char op[10], arg1[10], arg2[10], res[10];
} arr[20];

struct constant {
    char var[10];
    int val;
} table[20];

int table_cnt = 0;

int isNumber(char str[]) {
    return isdigit(str[0]) || (str[0] == '-' && isdigit(str[1]));
}

int main() {
    int n, i, j;

    printf("Enter number of quadruples: ");
    if (scanf("%d", &n) != 1) return 1;

    printf("Enter quadruples (op arg1 arg2 res):\n");
    for (i = 0; i < n; i++) {
        scanf("%s %s %s %s", arr[i].op, arr[i].arg1, arr[i].arg2, arr[i].res);
    }

    printf("\nOptimized Quadruples:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < table_cnt; j++) {
            if (strcmp(arr[i].arg1, table[j].var) == 0) {
                sprintf(arr[i].arg1, "%d", table[j].val);
            }
        }

        for (j = 0; j < table_cnt; j++) {
            if (strcmp(arr[i].arg2, table[j].var) == 0) {
                sprintf(arr[i].arg2, "%d", table[j].val);
            }
        }

        if (strcmp(arr[i].op, "=") == 0) {
            if (isNumber(arr[i].arg1)) {
                strcpy(table[table_cnt].var, arr[i].res);
                table[table_cnt].val = atoi(arr[i].arg1);
                table_cnt++;
            }
            printf("%s %s %s %s\n", arr[i].op, arr[i].arg1, arr[i].arg2, arr[i].res);
        }
        else if (isNumber(arr[i].arg1) && isNumber(arr[i].arg2)) {
            int v1 = atoi(arr[i].arg1);
            int v2 = atoi(arr[i].arg2);
            int res_val = 0;

            if (strcmp(arr[i].op, "+") == 0) res_val = v1 + v2;
            else if (strcmp(arr[i].op, "-") == 0) res_val = v1 - v2;
            else if (strcmp(arr[i].op, "*") == 0) res_val = v1 * v2;
            else if (strcmp(arr[i].op, "/") == 0 && v2 != 0) res_val = v1 / v2;

            strcpy(arr[i].op, "=");
            sprintf(arr[i].arg1, "%d", res_val);
            strcpy(arr[i].arg2, "?");

            strcpy(table[table_cnt].var, arr[i].res);
            table[table_cnt].val = res_val;
            table_cnt++;

            printf("%s %s %s %s\n", arr[i].op, arr[i].arg1, arr[i].arg2, arr[i].res);
        }
        else {
            printf("%s %s %s %s\n", arr[i].op, arr[i].arg1, arr[i].arg2, arr[i].res);
        }
    }

    return 0;
}
