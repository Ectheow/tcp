#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define VAR_MIN 'a'
#define VAR_MAX 'z'
#define MAXLINE 1000


double get_var(char name);
void set_var(char name, double value);
int getop(char[], char[]);
void push(double);
double pop(void);
double peek(void);
int m_getline(char line[], int maxline);

/* reverse Polish calculator */
main()
{
    int type, expect_var = 0;
    double op2, op1;
    char s[MAXOP], line[MAXLINE], var_name = '\0';

    while (m_getline(line,MAXLINE) && (type = getop(s, line)) != EOF) {
        if (type >= VAR_MIN && type <= VAR_MAX) {
            expect_var = 1;
            var_name = type;
        } else if(expect_var) {
            switch(type) {
                case '!':
                    if (!expect_var) {
                        printf("error: no variable specified\n");
                    } else 
                        set_var(var_name, pop());
                    break;
                case '@':
                    if (!expect_var) {
                        printf("error: no variable specified\n");
                    } else 
                        push(get_var(var_name));
                    break;
                default: 
                    printf("error: variable specified on stack but no variable operation given\n");
                    break;
            }
            expect_var = 0;
        } else switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '%':
                op2 = pop();
                op1 = pop();
                if (op2 <0 || op1 < 0) 
                    printf("error: %% only takes positive arguments\n");
                else
                    push((int)op1 % (int)op2);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor for /\n");
                break;
            case 'P':
                printf("\t%.8g\n", pop());
                break;
            case 'K':
                printf("\t%.8g\n", peek());
                break;
            case '^':
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case 'S':
                push(sin(pop()));
                break;
            case 'C':
                push(cos(pop()));
                break;
            case 'T':
                push(tan(pop()));
                break;
            case '\n':
                //printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
    
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

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[], char line[])
{
    int i, c, peek, j;

    j = 0;
    while ((s[0] = c = line[j++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;

    if (!isdigit(c) && !(c == '.'  || c == '-' || c == '+'))
        return c;
    else if(!isdigit(c) && (c == '-' || c == '+')) {
        if (line[j] == ' ' || line[j] == '\t' || line[j] == '\n') {
            return c;
        }
        c = s[++i] = line[j];
    } 

    if (isdigit(c))
        while (isdigit(s[++i] = c = line[j++]))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = line[j++]))
            ;
    s[i] = '\0';

    return NUMBER;
}

int m_getline(char line[], int maxline)
{
    int i, c;

    for(i=0; i<maxline && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n' && i < maxline-1)
        line[i++] = c;
    line[i] = '\0';
    return i;
}


#define BUFSIZE 100 

char buf[BUFSIZE];
int bufp=0;

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
