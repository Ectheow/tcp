#include <stdio.h>

/* prints a histogram of word lengths from input */

#define N_FREQS 60
#define IN 0
#define OUT 1

main()
{
    int freqs[N_FREQS];
    int c,state,len,i,j;

    for(i=0; i<N_FREQS;i++)
        freqs[i] = 0;
    len = 0;
    state = OUT;
    i=0;
    j=0;
    while((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n')  {
            state = OUT;
            ++freqs[len-1];
            len=0;
        }
        else if (state == OUT) {
            ++len;
            state = IN;
        } else
            ++len;
        
    }
    for (i=0;i<N_FREQS;i++) {
        printf("%4d |", i+1);
        for(j=0;j<freqs[i];j++) {
            printf("*");
        }
        printf("\n");
    }
}
