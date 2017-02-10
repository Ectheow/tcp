#include <stdio.h>

int bitcount(int x);
int m_getline(char line[], int maxline);
int atoi(char line[]);

#define MAXLINE 1000

int main()
{
    char line[MAXLINE];
    int i, n;

    for(i=0; i<MAXLINE; ++i)
        line[i] = 0;

    for (printf("n: "); m_getline(line, MAXLINE) != 0; printf("n: ")) {
        n = atoi(line);
        printf("%d\n", bitcount(n));
    }
    return 0;
}

int bitcount(int x)
{
    int count = 0;
    for(count = 0; x != 0; ++count) 
        x &= (x - 1);

    return count;
}

int atoi(char line[])
{
    int i,n;

    n = 0;
    for(i=0; line[i] >= '0' && line[i] <= '9'; ++i)
        n = n*10 + (line[i] - '0');

    return n;
}

int m_getline(char line[], int maxline)
{

    int c, i;

    for(i =0; (c = getchar()) != EOF && c != '\n' && i < maxline; ++i)
        line[i] = c;

    if (i < maxline-1 && c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}
