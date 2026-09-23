#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int i, error;

void E(void);
void T(void);
void Eprime(void);
void Tprime(void);
void F(void);

int main(void)
{
    i = 0;
    error = 0;

    printf("Enter an arithmetic expression: ");
    fgets(input, sizeof(input), stdin);

    /* Remove the newline added by fgets() */
    input[strcspn(input, "\n")] = '\0';

    E();

    if (input[i] == '\0' && error == 0)
        printf("\nAccepted..!!!\n");
    else
        printf("\nRejected..!!!\n");

    return 0;
}

void E(void)
{
    T();
    Eprime();
}

void Eprime(void)
{
    if (input[i] == '+')
    {
        i++;
        T();
        Eprime();
    }
}

void T(void)
{
    F();
    Tprime();
}

void Tprime(void)
{
    if (input[i] == '*')
    {
        i++;
        F();
        Tprime();
    }
}

void F(void)
{
    if (isalnum((unsigned char)input[i]))
    {
        i++;
    }
    else if (input[i] == '(')
    {
        i++;
        E();

        if (input[i] == ')')
            i++;
        else
            error = 1;
    }
    else
    {
        error = 1;
    }
}
