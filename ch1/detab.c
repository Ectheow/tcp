#include <stdio.h>

/* Program to replace tabs in the input with the proper number of blanks, to
 * space to the next tab stop. 
 */

#define TAB_STOP 8
#define MAXLINE 1000


main()
{
    int c, i;
    while ((c = getchar()) != EOF) 
        if (c == '\t') 
            for(i=0; i< TAB_STOP; i++)
                putchar(' ');
        else
            putchar(c);
}
