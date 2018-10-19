#include<stdio.h>
#include<stdlib.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

// get ascii index of alphabet
int get_alpha_index(char c);
// get alphabet from ascii index
char get_alpha_from_index(int code, bool is_alpha, bool is_upper);

int main(int argc, string argv[])
{
    if (argc > 1)
    {
        string s_key = argv[1];
        int key = atoi(s_key);
        string text = get_string("plaintext: ");
        int len = strlen(text);

        int ciphers[len];

        int i;
        for (i = 0; i < len; i++)
        {
            if (isalpha(text[i]))
            {
                ciphers[i] = (get_alpha_index(text[i]) + key) % 26;
            }
            else
            {
                // printf("text[%d] = %c => %d\n", i, text[i], text[i]);
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
