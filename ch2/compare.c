#include <stdio.h>

main()
{
    double x=1.0, y=2.0, z=3.0;
    float w;
    if (-1L < 1UL) {
        printf("As it should be\n");
    } else {
        printf("-1L > 1UL\n");
    }

    w = x + y + z;
    printf("%f\n", w);
}
