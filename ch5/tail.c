/* tail.c: print the last n lines of its input.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define MAXLINES 5
char *lines[MAXLINES];
char *_getline(void);
char *alloc(int n);
char *alloc2(int n);
void dealloc(char *tofree);
void dealloc2(char *tofree);

int main(int argc, char *argv[])
{
    unsigned long startline=0, lastline=0;
    int n, i;
    char *line = NULL, *newstore = NULL;

    if (argc > 2) {
        printf("Error: too many arguments just -N for arguments\n");
        return 1;
    } else {
        n = atoi(++argv[1]);
        n = n > MAXLINES ? MAXLINES : n;
    }

    while(line = _getline()) {
        if (lastline == MAXLINES) { 
            for (i = MAXLINES-1; i>=0; i--) {
                //printf("Dealloc lines %d\n", i);
                if (i > (MAXLINES-n)) {
                    newstore = alloc2(MAXLINE);
                    strcpy(newstore, lines[i]);
                    dealloc(lines[i]);
                    lines[i] = newstore;
                } else {
                    //printf("dealloc %d\n", i);
                    dealloc(lines[i]);
                }
            }
            for (i=0; i<n-1; i++) {
                newstore = alloc(MAXLINE);
                strcpy(newstore, lines[MAXLINES-(n-i-1)]);
                dealloc2(lines[MAXLINES-(n-i-1)]);
                lines[MAXLINES-(n-i-1)] = NULL;
                lines[i] = newstore;
                //printf("just reallocated %s to %d\n", newstore, i);
                //lines[i] = lines[MAXLINE-i-1];
            }
            lastline = n-1;
        }
        newstore = alloc(MAXLINE);
        strcpy(newstore, line);
        lines[lastline++] = newstore;
        //printf("lastline %d\n", lastline);
    }

    for(i=n; i>0; i--) {
        printf("%s", lines[lastline-i]);
    }
}

char  *_getline(void)
{
    static char storage[MAXLINE];
    char *line = storage;
    int i, c;

    for(i=0; (c = getchar()) != EOF && i<MAXLINE && c != '\n'; i++) 
        line[i] = c;
    if (c == '\n' && i < MAXLINE-1)
        line[i++] = '\n';
    line[i] = '\0';

    if (i == 0) {
        return NULL;
    } else {
        return line;
    }
}

#define STORAGESIZE (MAXLINES*MAXLINE)

char storage[STORAGESIZE];
char storage2[STORAGESIZE];
char *storage2p = storage2;
int next = 0;

char *alloc2(int n)
{
    if (storage2p+n < storage2 + STORAGESIZE)  {
        storage2p += n;
        return storage2p-n;
    } else
        printf("Error: alloc2 no more memory\n");
    return NULL;
}

void dealloc2(char *alloc2p)
{
    if (alloc2p >= storage2 && alloc2p < storage2p)
        storage2p = alloc2p;
}


char *alloc(int n)
{
    char *ret = NULL;

    if (next+n <= STORAGESIZE) {
        ret =  storage+next;
        next += n;
        //printf("alloc: next is: %d\n", next);
    } else {
        printf("Error: out of memory\n");
    }

    return ret;
}

void dealloc(char *tofree)
{
    if (tofree >= storage && tofree < storage + STORAGESIZE) {
        next = (tofree - storage);
        //printf("dealloc: next is: %d\n", next);
    } else {
        printf("Error: dealloc: no memory there\n");
    }
}
