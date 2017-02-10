#include <stdio.h>
#include <string.h>

#define MAXLINES 10000
#define MAXSTORE 8000000

char *lineptr[MAXLINES];
char storage[MAXSTORE];

int readlines(char *lineptr[], int nlines, char *storage, int maxstore);
void writelines(char *lineptr[], int nlines);

void _qsort(char *lineptr[], int left, int right);

/* sort input lines */
main()
{
    int nlines; /* number of input lines read */

    if ((nlines = readlines(lineptr, MAXLINES, storage, MAXSTORE)) >= 0) {
        _qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line */
int _getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *storage, int maxstore)
{
    int len, nlines;
    char *p=storage, line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines ||  (p + len)>= (storage + maxstore))
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i<nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* alloc functions */
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* requested size fits */
        allocp += n;
        return allocp - n;
    } else /* not enough memory */
        return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

/* qsort - sort an array of strings */
void _qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) /* do nothing, if array contains fewer than two elements */
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for(i = left + 1; i<= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    _qsort(v, left, last-1);
    _qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int _getline(char *line, int maxline)
{
    int i,c;
    for (i=0,c=0; (c = getchar()) != EOF && c != '\n' && i < maxline; i++)
        line[i] = c;
    if (i < maxline-1 && c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}
