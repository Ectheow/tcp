#include <stdio.h>

main()
{
    int c,is_escape;

    is_escape=0;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            is_escape = 1;
            c = 't';
        }

        if (c == '\b') {
            is_escape = 1;
            c = 'b';
        }
        if (c == '\\') {
            is_escape = 1;
            c = '\\';
        }

        if (is_escape)
            putchar('\\');
        putchar(c);
        is_escape = 0;
    }
}
