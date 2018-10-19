#include <stdio.h>
#include <cs50.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("main: x = %d, y = %d\n", x, y);

    swap(&x, &y);

    printf("main: x = %d, y = %d\n", x, y);
}

void swap(int *a, int *b)
{
    eprintf("[swap]: a = %d, b = %d\n", *a, *b);

    int temp = *a;
    *a = *b;
    *b = temp;

    eprintf("[swap]: a = %d, b = %d\n", *a, *b);
}