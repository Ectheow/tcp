#include <stdio.h>

#define MAXLINE 1000

/* reverse input lines */

void reverse(char s[], int len);
int m_getline(char s[], int len);

main()
{
    char line[MAXLINE];
    int len;

    while((len = m_getline(line, MAXLINE)) != 0) {
        reverse(line, len-1);
        printf("%s", line);
    }
    return 0;
}


void reverse(char s[], int len)
{
    int i,c1;

    for(i=0; i<len/2; ++i) {
        c1 = s[len-i-1];
        s[len-i-1] = s[i];
        s[i] = c1;
    }
}

/* getline: read a line into s, return length*/
int m_getline(char s[],int lim)
{
    int c,i;

    for(i=0; i<lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}
