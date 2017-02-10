#include <stdio.h>

#define swap(t, x, y) { \
    t tmp;              \
    tmp = x;            \
    x = y;              \
    y = tmp;            \
}

int main()
{
    int x = 1, y = 2;

    printf("%d, %d\n", x, y);
    swap(int, x, y);
    printf("%d, %d\n", x, y);
}
