#include<stdio.h>
#include<stdlib.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

int get_alpha_index(char c);
char get_alpha_from_index(int code, bool is_alpha, bool is_upper);

int main(int argc, string argv[])
{
    if (argc > 1)
    {
        int i;

        for (i = 0; i < strlen(argv[1]); i++)
        {
            if (!isalpha(argv[1][i]))
            {
                return 1;
            }
        }

        string key = argv[1];
        string text;
        if (argc > 2)
        {
            text = argv[2];
        }
        else
        {
            text = get_string("plaintext: ");
        }

        int len = strlen(text);

        int ciphers[len];

        int j = 0;
        for (i = 0; i < len; i++)
        {
            if (isalpha(text[i]))
            {
                ciphers[i] = (get_alpha_index(text[i]) + get_alpha_index(key[j % 3])) % 26;
                j++;
            }
            else
            {
                ciphers[i] = text[i];
            }
        }

        printf("ciphertext: ");
        for (i = 0; i < len; i++)
        {
            printf("%c", get_alpha_from_index(ciphers[i], isalpha(text[i]), isupper(text[i])));
        }
        printf("\n");

    }
    else
    {
        printf("ERROR!, invalid input\n");
        return 1;
    }

}

int get_alpha_index(char code)
{
    if (isupper(code))
    {
        return code - 65;
    }
    else
    {
        return code - 97;
    }
}

char get_alpha_from_index(int code, bool is_alpha, bool is_upper)
{
    if (is_alpha)
    {
        if (is_upper)
        {
            return code + 65;
        }
        else
        {
            return code + 97;
        }
    }
    else
    {
        return code;
    }
}
