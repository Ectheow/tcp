#include <stdio.h>

main()
{
    int c,blank;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            putchar(c);
            while((c = getchar()) == ' ')
                ;
        }
        if (c != EOF)
            putchar(c);
    }
}
