#include <stdio.h>

int strend(char *s, char *t);
int m_getline(char *s, int max);


#define MAXLINE 1000

main()
{

    long nmatch=0;
    char line[MAXLINE], grepline[MAXLINE];

    if (!m_getline(grepline, MAXLINE))
        return 0;
    while(m_getline(line, MAXLINE))
        if (strend(line, grepline)) {
            fprintf(stderr, "%s", line);
            nmatch++;
        }
    return nmatch;
}


int strend(char *s, char *t)
{
    char *send, *tend;

    for(send=s; *send; ++send)
        ;
    for(tend=t; *tend; ++tend)
        ;

    for(; *send == *tend; --send,--tend)
        ;

    return ++tend == t;
}

int m_getline(char *s, int max)
{
    char *p = s;
    int c;
    for(; (c = getchar()) != EOF &&
          c != '\n' ;
          p++)
        *p = c;

    if (c == '\n' && p-s < max-1)
        *p++ = c;
    *p = '\0';

    return p - s;
}
