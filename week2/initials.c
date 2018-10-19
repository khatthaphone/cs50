#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = get_string("Name: ");

    char initials[4];

    int i, counter = 0;
    for (i = 0; i < strlen(name); i++)
    {
        if (isupper(name[i]))
        {
            initials[counter] = name[i];
            counter++;
        }
    }

    initials[counter] = '\0';
    printf("initials = \"%s\" leng = %lu", initials, strlen(initials));
}