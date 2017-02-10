#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

void strcat(char *s, char *t);
int strlen(char *s);
char *itoa(char *s, int n);
void reverse(char *s);
int m_getline(char *line, int maxline);


int main()
{
    char line[MAXLINE], lineno[MAXLINE];
    int len, ln;

    for(ln = 0;(len = m_getline(line, MAXLINE)) != 0; ln++) {
        //line[len-1] = '\0';
        itoa(lineno, ln);
        strcat(lineno, ": ");
        strcat(lineno, line);
        printf("%s", lineno);
    }

    return 0;
}

void strcat(char *s, char *t)
{
    while(*s)
        s++;

    for(; *t;)
        *s++ = *t++;
    *s = '\0';
}

int m_getline(char *line, int maxline)
{
    char *l = line;
    int c;
    while((c = getchar()) != EOF && 
            c != '\n' &&  
            l - line < maxline)
        *l++ = c;

    if (c == '\n' && l - line < maxline-1)
        *l++ = c;
    *l = '\0';
    return l - line;
}

void reverse(char *s)
{
    int i, tmp, len=strlen(s);


    for(i=0; i<len/2; i++) {
        tmp = s[len-i-1];
        s[len-i-1] = s[i];
        s[i] = tmp;
    }
}

int strlen(char *s)
{
    char *p;

    for(p = s; *p; p++)
        ;
    return p-s;
}

char *itoa(char *s, int n)
{
    char *p = s;
    do {
        *p++ = n % 10 + '0';
    } while ((n/=10) != 0);

    *p = '\0';
    reverse(s);
    return s;
}
