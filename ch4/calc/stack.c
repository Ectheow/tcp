#include <stdio.h>
#include "calc.h"
#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0;
double val[MAXVAL]; /* value stack */ 


/* push: push f onto the value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double peek(void)
{
    if (sp > 0)
        return val[sp-1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

double variables[VAR_MAX-VAR_MIN];

double get_var(char name) 
{
    int idx = name - VAR_MIN;
    if (idx >= 0 && idx <= VAR_MAX)
        return variables[idx];
    else {
        printf("error: '%c': no such variable\n");
        return 0.0;
    }
}

void set_var(char name, double value)
{
    int idx = name - VAR_MIN;
    if (idx >= 0 && idx <= VAR_MAX) 
        variables[idx] = value;
    else {
        printf("error: '%c': no such variable\n");
    }
}


