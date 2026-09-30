#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][10] = {
    "int", "float", "char", "if", "else",
    "while", "for", "return"
};

int isKeyword(char word[])
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    char input[100];
    int i = 0;
    char word[20];
    int j;

    printf("Enter a statement: ");
    fgets(input, sizeof(input), stdin);

    while (input[i] != '\0')
    {
        /* Identifier or Keyword */
        if (isalpha(input[i]) || input[i] == '_')
        {
            j = 0;

            while (isalnum(input[i]) || input[i] == '_')
            {
                word[j++] = input[i++];
            }

            word[j] = '\0';

            if (isKeyword(word))
                printf("%s : Keyword\n", word);
            else
                printf("%s : Identifier\n", word);
        }

        /* Number */
        else if (isdigit(input[i]))
        {
            j = 0;

            while (isdigit(input[i]))
            {
                word[j++] = input[i++];
            }

            word[j] = '\0';

            printf("%s : Number\n", word);
        }

        /* Operator */
        else if (input[i] == '+' || input[i] == '-' ||
                 input[i] == '*' || input[i] == '/' ||
                 input[i] == '=')
        {
            printf("%c : Operator\n", input[i]);
            i++;
        }

        /* Special symbol */
        else if (input[i] == '(' || input[i] == ')' ||
                 input[i] == '{' || input[i] == '}' ||
                 input[i] == ';' || input[i] == ',')
        {
            printf("%c : Special Symbol\n", input[i]);
            i++;
        }

        /* Ignore spaces */
        else
        {
            i++;
        }
    }

    return 0;
}