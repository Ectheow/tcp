#include <stdio.h>
#include <ctype.h>
typedef  int bool;
#define true 1
#define false 0
/* expr.c: stack calculator, where arguments come from argv and are printed out.
 *
 * general procedure:
 *   for each argument:
 *      if it is a number, push it onto the stack.
 *      if it is an operator, evaluate it.
 *  print the top element on the stack.
 *  exit
 */


#define OPS "+-/*"

void push(double);
double pop(void);
double atod(char *, char **);
bool is_double(char *);
bool is_op(char *);
void eval_op(char *);


int main(int argc, char *argv[])
{
    char *invalid = NULL;
    while(--argc > 0) {
        if (is_double(*++argv)) {
            printf("double: %s\n", *argv);
            push(atod(*argv,  &invalid));
        } else if(is_op(*argv)) {
            printf("op: %s\n", *argv);
            eval_op(*argv);
        } else {
            printf("Error: unrecognized atom: %s\n", *argv);
            return -1;
        }
    }
    printf("%lf\n", pop());
    return 0;
}


void eval_op(char *op)
{
    double op2;

    switch (*op) {
        case '+':
            push(pop() + pop());
            break;
        case '-':
            op2 = pop();
            push(pop()-op2);
            break;
        case '*':
            push(pop()*pop());
            break;
        case '/':
            op2 = pop();
            push(pop()/op2);
            break;
        default:
            printf("Unrecognized operator: %c\n", *op);
            break;
    }
}

bool is_op(char *c)
{
    char *p;
    for(p = OPS; *p != '\0'; *p++) {
        if (*c == *p)
            return true;
    }
    return false;
}

bool is_double(char *c)
{

    if (*c == '+' || *c == '-' && *(c+1) == '\0')
        return false;

    for(; (*c >= '0' && *c <= '9') || *c == '.' || *c == '-' || *c == '+'; c++)
        ;

    return *c == '\0';
}

double atod(char *c, char **invalid)
{
    double num = 0;
    long pow = 1;
    char sign = '+';

    if (*c == '-' || *c == '+')
        sign = *c++;

    while (isspace(*c))
        c++;

    if (!(isdigit(*c) || *c == '.')) {
        *invalid = c;
        return 0;
    }

    while (isdigit(*c)) {
        num += num * 10.0 + (*c++ - '0');
    }

    if(*c == '.')
        c++;
    else
        goto end;

    while(isdigit(*c)) {
        num += num * 10 + *c++ - '0';
        pow *= 10;
    }

end:
    num /= pow;
    *invalid = c;
    return sign == '+' ? num : -1.0*num;
}

#define NR_STACK 1000
double stack[NR_STACK];
unsigned long stackp = 0;

void push(double d)
{
    if (stackp < NR_STACK) {
        printf("push: %lf\n", d);
        stack[stackp++] = d;
    } else {
        printf("Error: stack overflow\n");
    }
}

double pop()
{
    return stackp > 0 ? stack[--stackp] : 0;
}
