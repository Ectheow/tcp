#include <string.h>
#include <strings.h>
#include <stdio.h>
/*
 * get input from stdin, if the input line is a U followed by a newline
 * character, unget the last line of input before this one.  At EOF, print the
 * pusback buffer and anything in the main buffer.
 */

#define MAXLINE 1000
int getch();
void ungetch(int c);
void ungets(char s[]);


main()
{
    int c, i;
    char line[MAXLINE];
    i = 0;
    while((c = getch()) != EOF) {
        line[i++] = c;
        if (c == '\n') {
            line[i] = '\0';
            if (i >= 2 && line[i-2] == 'U')
                ungets(line);
            else
                printf("%s", line);
            i = 0;
        }
    }
}


#define MAXBUF 100
int buf[MAXBUF];
int bufp = 0;


int getch()
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp <= MAXBUF-1) {
        buf[bufp++] = c;
    } else {
        printf("ERROR: ungetch: out of buffer space\n");
    }
}

void ungets(char s[])
{
    int i;
    for(i=strlen(s)-1; i>=0; --i) {
        ungetch(s[i]);
    }
}

