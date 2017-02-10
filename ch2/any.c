#include <stdio.h>

#define MAXLINE 1000

int any(char s1[], char s2[]);
int m_getline(char line[], int maxline);


main() {
    int r,i;
    char line[MAXLINE], any_line[MAXLINE];

    for(i=0; i<MAXLINE; ++i)
        line[i] = any_line[i] = '\0';

    if ((r = m_getline(any_line, MAXLINE)) == 0)
        return 0;

    any_line[--r] = '\0';

    while((r = m_getline(line, MAXLINE)) > 0) {
        line[--r] = '\0';
        printf("%d\n", any(line, any_line));
    }
}

int any(char s1[], char s2[]) 
{
    int i,j;

    for(i=0; s1[i] != '\0'; ++i)
        for (j = 0; s2[j] != '\0'; ++j)
            if (s1[i] == s2[j])
                return i;

    return -1;
}

int m_getline(char line[], int maxline)
{
    int c,i;
    for(i=0; (c = getchar()) != EOF && c != '\n' && i< maxline; ++i)
        line[i] = c;

    if (c == '\n' && i < maxline)
        line[i++] = c;
    line[i] = '\0';

    return i;
}
