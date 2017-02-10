#include <stdio.h>

main()
{
    long c,nb,nt,nl;

    nb = 0;
    nt = 0;
    nl = 0;
    while((c = getchar()) != EOF) {
        if (c == '\t')
            ++nt;
        if (c == '\n')
            ++nl;
        if (c == ' ')
            ++nb;
    }

    printf("blanks: %d\n", nb);
    printf("tabs: %d\n", nt);
    printf("lines: %d\n", nl);
}
