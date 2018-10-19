#include<stdio.h>
#include<cs50.h>

int main(void)
{

    int height;

    do
    {
        printf("Height: ");
        height = get_int();
    }
    while (!(height >= 0) || !(height <= 23));

    int i, j, k;
    for (i = 0; i < height; i++)
    {
        // invisible pyramid
        for (j = height - i - 1; j > 0; j--)
        {
            printf(" ");
        }
        // left pyramid
        for (k = 0; k <= i; k++)
        {
            printf("#");
        }
        // 2 spaces gap
        printf("  ");
        // right pyramid
        for (k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");

    }

}