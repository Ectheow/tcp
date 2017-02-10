#include <stdio.h>

#define MAXLINE 1000

int htoi(char line[]);
int m_getline(char line[], int maxline);

main() {
    char line[MAXLINE];
    int i,n;

    for (i = 0; i<MAXLINE; ++i)
        line[i] = 0;

    while(m_getline(line, MAXLINE) != 0){
        n = htoi(line);
        if (n < 0)
            printf("Error\n");
        else
            printf("%d\n", n);
    }
}

int htoi(char line[]) 
{
    int i,num=0,adj=0,start=0;

    if (line[0] == '0' && (line[1] == 'x' || line[1] == 'X')) {
        start = 2;
    } else {
        start = 0;
    }

   for(i=start; line[i] != '\0' && line[i] != '\n'; ++i) {
        if (line[i] >= '0' && line[i] <= '9') {
            adj = -'0';
        } else if (line[i] >= 'a' && line[i] <= 'f') {
            adj = -'a' + 0xa;
        } else if (line[i] >= 'A' && line[i] <= 'F') {
            adj = -'A' + 0xa;
        } else {
            printf("Error\n");
            return -1;
        }
       num = num*0x10 + (line[i] + adj);
    }

    return num;
}

int m_getline(char line[], int maxline)
{
    int c,i;

    for(i=0; (c = getchar()) != EOF && c != '\n' && i < maxline; ++i)
        line[i] = c;

    if (i < maxline -1  && c == '\n')
        line[i++] = '\n';
    line[i] = '\0';

    return i;
}
