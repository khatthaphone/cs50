#include <stdio.h>
#include <cs50.h>

int main(void)
{

    string s = get_string();
    string t = get_string();

    if (s == t)
    {
        printf("same\n");
    }
    else
    {
        printf("different\n");
    }

}