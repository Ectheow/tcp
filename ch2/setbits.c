#include <stdio.h>
#include <limits.h>

int setbits(int x, int p, int n, int y);
int getnum(char prompt[]);
int printbin(int x);
int m_getline(char line[], int maxline);
int atoi(char integer[]);
int invert(int x, int p, int n);
int rightrot(int x, int n);


#define MAXLINE 1000


main()
{
    int n,i,x, y, p, r, quit, func;
    char line[MAXLINE];

    for(i=0; i<MAXLINE; ++i)
        line[i] = 0;



    quit = 0;
    while(!quit) {
        printf("> ");
        if (m_getline(line, MAXLINE) == 0)
            quit = 1;
        else {
            func = line[0];
        }
        if(func == 's') {
            if ((x = getnum("x: ")) == INT_MIN)
                return 0;

            if ((p = getnum("p: ")) == INT_MIN)
                return 0;

            if ((n = getnum("n: ")) == INT_MIN)
                return 0;

            if ((y = getnum("y: ")) == INT_MIN)
                return 0;

            printf("x == ");
            printbin(x);
            printf("y == ");
            printbin(y);
            printf("\n");

            r = setbits(x, p, n, y);
            printf("r == ");
            printbin(r);
        } else if (func == 'i') {
            if ( ((x = getnum("x: ")) == INT_MIN) ||
                 ((p = getnum("p: ")) == INT_MIN) ||
                 ((n = getnum("n: ")) == INT_MIN))
                return 0;
            
            printf("x == ");
            printbin(x);
            printf("y == ");
            printbin(y);
            printf("\n");

            r = invert(x, p, n);
            printf("r == ");
            printbin(r);
        } else if (func == 'r') {
            if ( 
                    ((x = getnum("x: ")) == INT_MIN) ||
                    ((n = getnum("n: ")) == INT_MIN)) 
                return 0;

            printf("x == ");
            printbin(x);
            printf("y == ");
            printbin(y);
            printf("\n");

            r = rightrot(x, n);
            printf("r == ");
            printbin(r);
        } else {
            printf("???!\n");
        }

        if (!quit) {
            printf("again? > ");
            if (!m_getline(line, MAXLINE) || line[0] == 'n' || line[0] == 'N')
                quit = 1;
        }
    }
    return 0;
}


int setbits(int x, int p, int n, int y)
{
    return ( 
            ( 
             ( (~((( 1 << n ) - 1) << (p - n + 1)) | ( 1 << (p-n + 1) -1) ) & x)
            ) | ( 
             ( ( ( 1 << n ) - 1) & y ) << (p - n + 1)) 
            );
}

int printbin(int x)
{
    int nbits = sizeof(int)*8, i;

    for(i=nbits-1; i >= 0; --i) {
        printf("%d", ((1<<i & x) != 0));
    }
    printf("\n");
}

int m_getline(char line[], int maxline)
{
    int c, i;

    for(i=0; (c = getchar()) != EOF && c != '\n' && i < maxline; ++i)
        line[i] = c;

    if (c == '\n' && i < maxline)
        line[i++] = c;

    line[i] = '\0';

    return i;
}

int atoi(char integer[])
{
    int n, i;

    n = 0;

    for(i = 0; integer[i] >= '0' && integer[i] <= '9'; ++i) {
        n *= 10;
        n += (integer[i] - '0');
    }
    return n;
}

int getnum(char prompt[])
{
    char line[MAXLINE];
    int i;

    for (i = 0; i< MAXLINE; ++i)
        line[i] = 0;

    printf("%s", prompt);
    if (m_getline(line, MAXLINE) == 0) {
        return INT_MIN;
    } else {
        return atoi(line);
    }
}

int invert(int x, int p, int n)
{
    int inverted = (( (x >> (p + 1 - n)) ^ ~0
                    ) & 
                    ( (1 << n) -1))
        << (p - n + 1);

    int maskout = ((~0) << (p + 1)) |  ((1 << (p - n + 1))-1);

    x &= maskout;
    x |= inverted;

    return x;
}

int rightrot(int x, int n)
{
    int xleft = (((1<<n)-1) & x) << (32 - n);

    x >>= n;
    x |= xleft;

    return x; 
}
