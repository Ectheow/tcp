#include <stdio.h>
char *strncpy(char *s, char *t, int n);
char *strncat(char *s, char *t, int n);
int strncmp(char *s, char *t, int n);

char *texpr;
#define TEXPR(exp) ((texpr=#exp),(exp))
#define MAXLINE 1000
#define OK printf("OK: %s\n", texpr)
#define NOT_OK printf("NOT OK: %s\n", texpr)

int main()
{
    char line[MAXLINE];

    line[0] = '\0';
    strncpy(line, "cats dogs", 4);
    if (TEXPR(strncmp(line, "cats", 4)) == 0) 
        OK;
    else
        NOT_OK;

    if (TEXPR(strncmp(line, "catsblegh", 20)) < 0) 
        OK;
    else
        NOT_OK;

    strncat(line, " dogs", 4);
    printf("%s\n", line);
    if (TEXPR(strncmp(line, "cats dog", 8)) == 0) 
        OK;
    else
        NOT_OK;

    if (TEXPR(strncmp(line, "cats dogs", 200)) == 0)
        OK;
    else
        NOT_OK;

    if (TEXPR(strncmp(line, "d", 20)) < 0)
        OK;
    else
        NOT_OK;

    if (TEXPR(strncmp(line, "d", 1)) < 0)
        OK;
    else 
        NOT_OK;
}

char *strncpy(char *s, char *t, int n)
{
    char *p;

    for(p = s; *t && p-s < n; ++p,++t)
        *p = *t;
    *p = '\0';

    return s;
}

int strncmp(char *s, char *t, int n)
{
    
    char *p;

    for(p=s; *(p+1) && *(t+1) && *p==*t && p-s < n-1; p++,t++)
        ;
    printf("p: '%c' t: '%c', p-s: %ld\n", *p, *t, p-s);
    if(*p==*t && !*(p+1) && *(t+1) && p-s < n-1) 
        return -*(t+1);
    else if (*p == *t && *(p+1) && !*(t+1) && p-s < n-1) 
        return *(p+1);
    else
        return *p-*t;
}

char *strncat(char *s, char *t, int n)
{
    char *sp, *tp;

    for(sp=s; *sp; ++sp)
        ;

    for(tp=t; *tp && tp-t <= n; sp++,tp++)
        *sp=*tp;
    *sp = '\0';
    return s;
}
