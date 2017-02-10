#include <stdio.h>

void squeeze(char s[], char c[]);
int m_getline(char s[], int maxline);

#define MAXLINE 1000


main()
{
    char squeezes[MAXLINE], line[MAXLINE];
    int i;

    for (i=0; i<MAXLINE; ++i) 
        squeezes[i] = line[i] = 0;

    printf("squeezes: ");
    if (m_getline(squeezes, MAXLINE) == 0)
        return 0;
    squeeze(squeezes, "\n");

    while(m_getline(line, MAXLINE) != 0) {
        squeeze(line, squeezes);
        printf("%s", line);
    }
}

void squeeze(char s[], char c[])
{
    int nouse,i,j,k;

    nouse = 0;
    k = 0;
    for(i=0; s[i] != '\0'; ++i)  {

        for(j=0; c[j] != '\0'; ++j)
            if (c[j] == s[i])
                nouse=1;

        if (!nouse)
            s[k++] = s[i];
        nouse = 0;
    }
    s[k] = '\0';
}


int m_getline(char s[], int maxline)
{
    int i=0,c=0;

    for(i=0; (c = getchar()) != EOF && i < maxline && c != '\n'; ++i)
        s[i] = c;

    if (i < maxline - 1 && c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}
