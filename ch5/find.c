#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int _getline(char *line, int max);

/* find: print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
    char line[MAXLINE];
    int found = 0;

    if (argc != 2)
        printf("Usage: find pattern\n");
    else
        while (_getline(line, MAXLINE) > 0)
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
            }
    return found;
}

int _getline(char *line, int max)
{
    int c;
    char *p = line;

    while((c = getchar()) != EOF && c != '\n' && p -line < max)
        *p++ = c;

    if (c == '\n' && p-line < max-1)
        *p++ = c;

    return p - line;
}
