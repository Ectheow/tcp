#include <stdio.h>

main()
{
    int c;

    c = getchar();

    if (c == 'a')
        printf("AEE\n");



    else {
        if (c == 'b')
            printf("BEE\n");
        else {
            if (c == 'c')
                printf("see\n");
            else {
                if (c == 'z')
                    printf("zeee\n");
                else
                    printf("else1\n");
            }
        }
    }
}
