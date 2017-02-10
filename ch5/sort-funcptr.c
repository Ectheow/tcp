#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(void *lineptr[], int left, int right, 
            int (*comp)(void *, void *));
int numcmp(char *, char *);

main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        _qsort((void **)lineptr, 0, nlines-1,
              (int (*)(void *, void *))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void _qsort(void *v[], int left, int right, 
            int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    _qsort(v, left, last-1, comp);
    _qsort(v, last+1, right, comp);
}

#include <stdlib.h>
/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
	return -1;
    else if (v1 > v2)
	return 1;
    else
	return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

char *alloc(int nbytes);
void dealloc(char *tofree);
int _getline(char *line, int maxline);

#define MAXLINE 1000
int readlines(char *lineptr[],  int nlines)
{
    static char line[MAXLINE];
    char *p;
    
    int i, linesize;
    for (linesize=i=0; (linesize = _getline(line, MAXLINE)) && i < nlines; i++) {
	if ((p = alloc(linesize)) == NULL) {
	    printf("Error: out of memory -- lines are too long!\n");
	    return -1;
	} else {
	    strcpy(p, line);
	    lineptr[i] = p;
	}
    }

    if (linesize > 0 && i == nlines) {
	printf("Error: out of memory -- too many lines!\n");
	return -1;
    } else
	return i;
}

void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i=0; i<nlines; i++)  {
	printf("%s", lineptr[i]);
    }
}

#define MEMSIZE 5000
char memory[MEMSIZE];
char *nextfree = memory;


char *alloc(int size)
{
    if (nextfree+size <= memory+MEMSIZE) {
	nextfree+=size;
	return nextfree-size;
    } else 
	return NULL;
}

void dealloc(char *start)
{
    if (start >= memory)
	nextfree = start;
}


int _getline(char *line, int maxline)
{
    int i, c;

    for(i=0; (c = getchar()) != EOF && c != '\n' && i<maxline; i++)
	line[i] = c;

    if (i < maxline-1 && c == '\n')
	line[i++] = c;
    if (i > 0)
	line[i++] = '\0';
    return i;
}
