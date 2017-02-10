#include <stdio.h>

main()
{
    short i = 0x8ff3;
    unsigned char j;

    printf("i: %d\n",
            i);
    j = i;
    printf("j: %d\n",
            j);
}
