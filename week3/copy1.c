#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(void) {

    char *s = get_string("s: ");
    if (!s)
    {
        return 1;
    }

    char *t = malloc(strlen(s) + 1 * sizeof(char));

    int i;
    for (i = 0; i < strlen(s); i++)
    {
        t[i] = s[i];
    }

    if (!t)
    {
        return 1;
    }

    t[0] = toupper(t[0]);

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);
    return 0;

}