#include <stdio.h>
/*
 * display a vertical histogram like so:
 * graphing:
 * row_num <- max frequency
 * while row_num != 0
 *  for each column
 *     if the column's corresponding frequency is gte the row num
 *         put a *
 *     else
 *         put a ' '
 *  row_num <- row_num-1
 * 
 */

#define N_FREQS 60
#define IN 0
#define OUT 1


main()
{
    int freqs[N_FREQS];
    int c,state,len,i,j,max_freq,longest_len;

    for(i=0; i<N_FREQS;i++)
        freqs[i] = 0;

    len=0;
    state=OUT;
    i = 0;
    j = 0;
    max_freq=0;
    longest_len=0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            state = OUT;
            ++freqs[len-1];
            if(freqs[len-1] > max_freq) 
                max_freq = freqs[len-1];
            if(len > longest_len)
                longest_len = len;

            len=0;
        }
        else if (state == OUT) {
            ++len;
            state = IN;
        } else
            ++len;
    }

    for(i=0;i<max_freq;i++) {
        for(j=0;j<N_FREQS;j++) {
            putchar(' ');
            if(freqs[j] >= max_freq-i) 
                putchar('*');
            else
                putchar(' ');
            putchar(' ');
        }
        putchar('\n');
    }

    for(i=0;i<longest_len;i++) {
        if (i==0)
            printf("%2d", i+1);
        else
            printf("%3d", i+1);
    }
    printf("\n");
}
