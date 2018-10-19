#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<unistd.h>
#include<crypt.h>

#define _XOPEN_SOURCE

int main(int argc, string argv[])
{
    if (argc > 1)
    {
        string uhash = argv[1];
        char salt[2];

        salt[0] = uhash[0];
        salt[1] = uhash[1];

        // printf("uhash = %s\nsalt = %s", uhash, salt);

        int i, k, l, m, n, o, p;
        for (i = 0; i < 5; i++)
        {
            char password[i + 1];

            // for (j = 0; j <= i; j++) password[j] = ' ';

            // printf("i = %d\n", i);

            for (k = 65; k <= 122; k++)
            {
                if (k == 91) k = 97;

                for (l = 0; l <= i; l++)
                {
                    password[0] = k;

                    if (l > 0)
                    {
                        for (m = 65; m <= 122; m++)
                        {
                            if (m == 91) m = 97;
                            {
                                password[1] = m;

                                if (l > 1)
                                {
                                    for (n = 65; n <= 122; n++)
                                    {
                                        if (n == 91) n = 97;
                                        {
                                            password[2] = n;

                                            if (l > 2)
                                            {
                                                for (o = 65; o <= 122; o++)
                                                {
                                                    if (o == 91) o = 97;
                                                    {
                                                        password[3] = o;

                                                        if (l > 3)
                                                        {

                                                            for (p = 65; p <= 122; p++)
                                                            {
                                                                if (p == 91) p =97;

                                                                password[4] = p;

                                                                // printf("%s\n", password);
                                                                if (strcmp(crypt(password, salt), uhash) == 0)
                                                                {
                                                                    printf("%s\n", password);
                                                                    return 0;
                                                                }

                                                            }

                                                        } else {
                                                            // printf("%s\n", password);
                                                            if (strcmp(crypt(password, salt), uhash) == 0)
                                                            {
                                                                printf("%s\n", password);
                                                                return 0;
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                // printf("%s\n", password);
                                                if (strcmp(crypt(password, salt), uhash) == 0)
                                                {
                                                    printf("%s\n", password);
                                                    return 0;
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    // printf("%s\n", password);
                                    if (strcmp(crypt(password, salt), uhash) == 0)
                                    {
                                        printf("%s\n", password);
                                        return 0;
                                    }
                                }
                            }
                        }
                    } else {
                        // printf("%s\n", password);
                        if (strcmp(crypt(password, salt), uhash) == 0)
                        {
                            printf("%s\n", password);
                            return 0;
                        }
                    }

                }
            }
        }
    }
}