#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len;
char act[15];

void check(void)
{
    int flag;
    int len_st;

    // Loop to continuously reduce handles until no more match
    do
    {
        flag = 0;
        len_st = strlen(stack);

        // Reduce single terminals: E -> a or E -> b
        if (len_st >= 1 && (stack[len_st - 1] == 'a' || stack[len_st - 1] == 'b'))
        {
            char reduced = stack[len_st - 1];
            stack[len_st - 1] = 'E';
            printf("\n \(%s\t\t%s\)\t\t\tE->%c", stack, ip_sym + ip_ptr, reduced);
            flag = 1;
        }
        // Reduce binary expressions: E -> E+E, E -> E*E, E -> E/E
        else if (len_st >= 3)
        {
            if (strcmp(stack + len_st - 3, "E+E") == 0)
            {
                stack[len_st - 3] = 'E';
                stack[len_st - 2] = '\0';
                st_ptr -= 2;
                printf("\n \(%s\t\t%s\)\t\t\tE->E+E", stack, ip_sym + ip_ptr);
                flag = 1;
            }
            else if (strcmp(stack + len_st - 3, "E*E") == 0)
            {
                stack[len_st - 3] = 'E';
                stack[len_st - 2] = '\0';
                st_ptr -= 2;
                printf("\n \(%s\t\t%s\)\t\t\tE->E*E", stack, ip_sym + ip_ptr);
                flag = 1;
            }
            else if (strcmp(stack + len_st - 3, "E/E") == 0)
            {
                stack[len_st - 3] = 'E';
                stack[len_st - 2] = '\0';
                st_ptr -= 2;
                printf("\n \(%s\t\t%s\)\t\t\tE->E/E", stack, ip_sym + ip_ptr);
                flag = 1;
            }
        }
    } while (flag == 1);
}

int main(void)
{
    printf("\n\t\t SHIFT REDUCE PARSER\n");
    printf("\n GRAMMAR\n");
    printf("\n E->E+E\n E->E/E");
    printf("\n E->E*E\n E->a/b\n");

    printf("\n Enter the input symbol:\t");
    if (scanf("%14s", ip_sym) != 1)
    {
        return 1;
    }

    len = strlen(ip_sym);

    printf("\n\t Stack implementation table");
    printf("\n Stack \t\t Input symbol\t\t Action");
    printf("\n________\t\t____________\t\t____________\n");
    printf("\n \(\t\t%s\)\t\t\t--", ip_sym);

    for (int i = 0; i < len; i++)
    {
        snprintf(act, sizeof(act), "shift %c", ip_sym[ip_ptr]);

        stack[st_ptr] = ip_sym[ip_ptr];
        st_ptr++;
        stack[st_ptr] = '\0';
        ip_ptr++;

        printf("\n \(%s\t\t%s\)\t\t\t%s", stack, ip_sym + ip_ptr, act);

        check();
    }

    if (strcmp(stack, "E") == 0 && ip_ptr == len)
    {
        printf("\n \(%s\t\t%s\)\t\t\tACCEPT\n", stack, ip_sym + ip_ptr);
    }
    else
    {
        printf("\n \(%s\t\t%s\)\t\t\tREJECT\n", stack, ip_sym + ip_ptr);
    }

    return 0;
}
