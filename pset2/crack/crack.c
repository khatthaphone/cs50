#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<unistd.h>
#include<crypt.h>

#define _XOPEN_SOURCE

void inner_loop(char *uhash, char *salt, int length, int position, char *password)
{

    int i;
    for (i = 65; i <= 122; i++)
    {
        if (i == 91)
        {
            i = 97;
        }
        password[position] = i;
        printf("%s\t", password);

        if (strcmp(crypt(password, salt), uhash) == 0)
        {
            printf("\n%s\n", password);
        }

        if (position < length - 1 && length != 1)
        {
            inner_loop(uhash, salt, length, position + 1, password);
        }
    }
}

void loop_print(char *uhash, char *salt, int length)
{
    int i, j;
    for (i = 0; i < length; i++)
    {
        char password[i + 1];
        int position = i;

        for (j = 0; j <= i; j++)
        {
            password[j] = ' ';
        }

        inner_loop(uhash, salt, length, position, password);
    }
}

int main(int argc, string argv[])
{
    if (argc > 1)
    {
        string uhash = argv[1];
        char salt[2];

        salt[0] = uhash[0];
        salt[1] = uhash[1];

        // printf("uhash = %s\nsalt = %s", uhash, salt);
        int length = 5;

        loop_print(uhash, salt, length);

    }
}