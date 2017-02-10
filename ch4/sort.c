#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNUMS 1000
#define MAXLINE 1000

/*
 * sort an array of integers given on stdin, separated by whitespace.
 */

int atoi_(char s[]);
void itoa_(char s[], int n);
void qsort_(int v[], int left, int right);


main()
{
    int nums[MAXNUMS], arrsize, i, n, c;
    char buf[MAXLINE];

    i=0;
    n=0;
    do {
        c = getchar();
        if (c == '\t' || c == ' ' || c == '\n' || c == EOF) {
            if (i > 0) {
                buf[i] = '\0';
                nums[n++] = atoi(buf);
            }
            i = 0;
        } else if (c >= '0' && c <= '9') 
            buf[i++] = c;
        else {
            printf("Error: unsure about '%c'\n", c);
            exit(EXIT_FAILURE);
        }
    } while(c != EOF);

    qsort_(nums, 0, n-1);
    for(i = 0; i<n; ++i) {
        itoa_(buf, nums[i]);
        puts(buf);
    }
}


int atoi_(char s[])
{
    int n, i;
    for(n=0,i=strlen(s)-1; i>=0;  --i) {
        if (!(s[i] >= '0' && s[i] <= '9')) {
            break;
        }
        n += n*10 + s[i]-'0';
        
    }
    return n;
}

void qsort_(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right)
        return;

    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i<=right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort_(v, left, last-1);
    qsort_(v, last+1, right);
}

void itoa_(char s[], int n)
{
    int i;
    s[0] = '\0';

    if (n/10) 
        itoa_(s, n/10);
    
    i = strlen(s);
    s[i++] = n%10 + '0';
    s[i] = '\0';
}

void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
