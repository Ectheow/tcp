#include <stdio.h>


/* fold long input lines into multiple shorter lines, after the last non-blank
 * character that occurs before the n-th column of input.
 */

#define MAX_BUF 1000
#define COL_LIMIT 50

void print_buffer(char buf[], int max, int col_limit);
void insert_buffer(char buf[],char c, int index, int max);

char buf[MAX_BUF];

main()
{
    int cols,c,i,last_blank;

    cols = 0;
    last_blank = -1;
    for (i=0; i< MAX_BUF; ++i) 
        buf[i] = '\0';

    for(i=0; ((c = getchar()) != EOF) && i < MAX_BUF; ++i) {
        buf[i] = c;
        if (i < MAX_BUF-1) 
            buf[i+1] = '\0';
        else
            buf[i] = '\0';        

        if (c == '\n')  {
            print_buffer(buf, i+1, COL_LIMIT);
            i= -1;
        }

    }
}


void print_buffer(char buf[], int max, int col_limit) {
    int i,last_blank,col;

    last_blank = -1;
    for(i=0,col=0; i<max && buf[i] != '\0'; ++i,++col) {
        if(buf[i] == ' ' || buf[i] == '\t') {
            last_blank = i;
        }
        if (col > col_limit && last_blank >= 0) {
            buf[last_blank] = '\n';
/* insert_buffer(buf, '\n', last_blank, max);*/
            last_blank = -1;
            col = -1;
            ++i;
        }
    }
    printf("%s", buf);
    for(i=0; i<max; ++i)
        buf[i] = '\0';
}

/* insert c at index, preserving the array. 
 * spills the last char in buf.
 */
void insert_buffer(char buf[], char c, int index, int max) {
    int i;
    
    for(i=max-1; i > index; --i) {
        buf[i] = buf[i-1];
    }
    buf[index] = c;
}
