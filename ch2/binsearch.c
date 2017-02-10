#include <stdio.h>

#define MAXLINE 1000
#define ARR_LEN 1000
int binsearch(int x, int v[], int n);
int atoi(char num[]);
int m_getline(char line[], int maxline);

int main()
{
    int sorted_array[ARR_LEN];
    int i,c,x,j;
    char line[MAXLINE];
    char num[MAXLINE];

    for(i=0; i<ARR_LEN; ++i)
        sorted_array[i] = 0;
    for(i = 0; i<MAXLINE; ++i)
        num[i] = line[i] = 0;

    j = 0;
    for(i=0; (c = getchar()) != 'q' && j < ARR_LEN && i < MAXLINE;) {
        if (c != '\t' && c != '\n' && c != ' ' && c <= '9' && c >= '0') 
            num[i++] = c;
        else {
            sorted_array[j++] = atoi(num);
            for(i = 0; i<MAXLINE; ++i)
                num[i] = 0;
            i = 0;
        }
    }

    while ((c = getchar()) != '\n')
        ;
    printf("> ");
    if (m_getline(line, MAXLINE) == 0)
        return 0;
    x = atoi(line);
    printf("%d: %d\n", x, binsearch(x, sorted_array, j+1));
}

/*
 * binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]
 */
int binsearch(int x, int v[], int n)
{
    int low,high,mid;

    low=0;
    high = n-1;
    while (low <= high && v[mid] != x) {
        mid = (low+high)/2;
        if (x < v[mid])
            high = mid-1;
        else 
            low = mid+1;
    }

    if (x == v[mid])
        return mid;
    else {
        printf(" mid: %d, v[mid] = %d, x:  = %d\n", mid, v[mid], x);
        return -1;
    }
}

int atoi(char num[])
{
    int i,n;

    for(i = 0; num[i] == ' ' || num[i] == '\t' || num[i] == '\n'; ++i)
        ;
    n = 0;
    for(; num[i] >= '0' && num[i] <= '9'; ++i)
        n = n*10 + (num[i] - '0');
    return n;
}

int m_getline(char line[], int maxline)
{
    int i,c;

    c = 0;
    for(i=0; (c = getchar()) != EOF && c != '\n' && i < maxline; ++i)
        line[i] = c;

    if (i < maxline-1 && c == '\n')
        line[i++] = c;

    line[i] = '\0';
    return i;
}
