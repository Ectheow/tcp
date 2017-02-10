#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c, peek;
    static int pushback=0, is_pushback=0;

    s[0] = c = (is_pushback ? pushback : getch());
    is_pushback = 0; 
    for(; c == ' ' || c == '\t'; s[0] = c = getch())
        ;
    s[1] = '\0';
    i = 0;

    if (!isdigit(c) && !(c == '.'  || c == '-' || c == '+'))
        return c;
    else if(!isdigit(c) && (c == '-' || c == '+')) {
        if ((peek = getch()) == ' ' || peek == '\t' || peek == '\n') {
            pushback=peek;
            is_pushback=1;
            return c;
        }
        c = s[++i] = peek;
    }

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';

    is_pushback = 1;
    pushback = c;

    return NUMBER;
}


