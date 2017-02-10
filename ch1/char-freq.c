#include <stdio.h>

#define MIN_ASCII ' '
#define MAX_ASCII '}'
main()
{
    int frequencies[MAX_ASCII-MIN_ASCII+1],c,max_freq,i,j;

    for(i=0;i<MAX_ASCII-MIN_ASCII;++i)
        frequencies[i] = 0;

    i = j = max_freq = 0;

    while ((c = getchar()) != EOF) {
        if (c <= MAX_ASCII && c >= MIN_ASCII)
            ++frequencies[c-MIN_ASCII];
        if (frequencies[c-MIN_ASCII] > max_freq)
            max_freq = frequencies[c-MIN_ASCII];
    }

    for (i=0;i<max_freq;i++) {
        for(j=0;j<MAX_ASCII-MIN_ASCII;j++) {
            putchar(' ');
            if (frequencies[j] >= max_freq - i) 
                putchar('*');
            else 
                putchar(' ');
            putchar(' ');
        }
        putchar('\n');
    }

    for(i=MIN_ASCII; i<MAX_ASCII; i++) {
        printf("'%c'", i);
    }
    putchar('\n');

}
