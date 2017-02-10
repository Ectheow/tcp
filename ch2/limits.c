#include <limits.h>
#include <float.h>
#include <stdio.h>

main() 
{
    printf("int min: %d int max: %d\n",
          INT_MIN,
          INT_MAX);
    printf("long min: %ld long max: %ld\n",
            LONG_MIN,
            LONG_MAX);
    printf("short min: %d short max: %d\n",
            SHRT_MIN,
            SHRT_MAX);
    printf("llong min: %lld llong max: %lld\n",
            LLONG_MIN,
            LLONG_MAX);

    printf("-----\n");
    printf(" float radix: %d\n"
           " float decimal digits: %d\n"
           " float min exp: %d\n"
           " float min 10 exp: %d\n",
           FLT_RADIX,
           FLT_DIG,
           FLT_MIN_EXP,
           FLT_MIN_10_EXP);
}
