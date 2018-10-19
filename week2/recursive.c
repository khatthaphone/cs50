#include<stdio.h>

void recursive(int m, int n);

int main(void) {
    recursive(100, 1);
}

void recursive(int m, int n) {
    if (m >= n) {
        printf("%d ", n);
        recursive(m, n+1);
    }
}