#include <stdio.h>

int m_getline(char line[], int maxline);

const int MAXLINE = 1000;
main()
{
    char line[MAXLINE];
    int i;

    for(i = 0; i<MAXLINE; ++i)
        line[i] = '\0';
    while(m_getline(line, MAXLINE) != 0) 
        printf("%s", line);

    return 0;
}

int m_getline(char line[], int maxline) 
{
    int i=0,c=0,quit=0;
    while(quit != 1) {
        c = getchar();
        if (c == EOF)
            quit = 1;
        else if (i == maxline-1)
            quit = 1;
        else if (c == '\n') { 
            quit = 1;
            line[i] = c;
            ++i;
        } else {
            line[i] = c;
            ++i;
        }
    }

    line[i] = '\0';

    return i;
}
