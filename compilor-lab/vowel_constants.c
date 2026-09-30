#include <stdio.h>
#include <ctype.h>

int main()
{
    char s[100];
    int i, v = 0, c = 0;

    printf("Enter string: ");
    fgets(s, 100, stdin);

    for (i = 0; s[i] != '\0'; i++)
    {
        if (isalpha(s[i]))
        {
            if (s[i]=='a' || s[i]=='e' || s[i]=='i' ||
                s[i]=='o' || s[i]=='u')
                v++;
            else
                c++;
        }
    }

    printf("Vowels = %d\n", v);
    printf("Consonants = %d\n", c);

    return 0;
}