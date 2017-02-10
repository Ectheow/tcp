#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 1000
main()
{
    int array[SIZE], getint(int *), n, i, c, getfloat(double *);
    double farray[SIZE];

    for(n = 0; n < SIZE && 
            ((c = getfloat(&farray[n])) != EOF) && 
            (isdigit(c) || isspace(c)); 
        n++)
        ;
    for(i=0; i<n; i++)
        printf("%lf\n", farray[i]);

}

int getch();
void ungetch(int);

int getfloat(double *pd)
{
    int c, sign, signchar;
    double power = 1.0;

    while(isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF &&
            c != '-' &&
            c != '+' && 
            c != '.')
    {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    signchar = c;

    if ((c == '+' || c == '-')
            && !isdigit(c = getch())) {
        ungetch(c);
        ungetch(signchar);
        return signchar;
    }

    for (*pd = 0.0; isdigit(c); c = getch()) {
        *pd = 10 * *pd + (c - '0');
    }

    if (c != '.') {
        if (c != EOF)
            ungetch(c);
        return c;
    }

    for(c=getch(),power = 1.0; isdigit(c); c = getch()) {
        *pd = 10 * *pd + (c - '0');
        power *= 10;
    }

    *pd /= power;
    *pd *= sign;

    if (c != EOF)
        ungetch(c);
    return c;
}

/* getint: get next ingeger from input into *pn */
int getint(int *pn)
{
    int c,sign,signchar;

    while(isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    signchar = c;
    if ((c == '+' || c == '-') && !isdigit(c = getch())) {
            ungetch(c);
            ungetch(signchar);
            return signchar;
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

    if (c != EOF)
        ungetch(c);
    return c;
}


#define MAXCHAR 100
int bp = 0;
char buf[MAXCHAR];

int getch()
{
    return (bp > 0) ? buf[--bp] : getchar();
}

void ungetch(int ch)
{
    if (bp < MAXCHAR-1)
        buf[bp++] = ch;
    else
        printf("error: out of pushback space\n");
}
