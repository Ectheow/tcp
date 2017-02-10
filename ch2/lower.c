#include <stdio.h>

int lower(int c);

int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        printf("%c", lower(c));
    }
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c - ('A' - 'a') : c;
}
