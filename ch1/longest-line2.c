#include <stdio.h>
#define MAXLINE 10 /* maximum input line size */

int m_getline(char s[], int lim);
void copy(char to[], char from[]);

/* print longest input line */
main()
{
    int len; /* current line length */
    int max; /* maximum length seen thus far */
    char line[MAXLINE]; /* current input line */
    char longest[MAXLINE]; /*longest line saved here */

    max = 0;
    while ((len = m_getline(line,MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0)
        printf("%s", longest);
    return 0;
}

/* getline: read a line into s, return length*/
int m_getline(char s[],int lim)
{
    int c,i,j;

    j = 0;
    for(i=0; i<lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (i == lim-1 && c != EOF)
        for (j=i; (c = getchar()) != EOF && c != '\n'; ++j)
            ;

    /* overwrite the last char w/ a newline if we're out of space */
    if (c == '\n') {
        if (i == lim-1) /* i is set to last viable index, so overwrite i-1 w/ newline */
            s[i-1] = c;
        else {
            s[i] = c;
            ++i; /* i is not lim-1, which means it is at least lim-2, so increment it */
        }
    }

    s[i] = '\0';

    if (j > i)
        return j;
    else
        return i;
}


/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while((to[i] = from[i]) != '\0')
        ++i;
}


