#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
int getline_(char s[], int maxline);
void reverse(char s[], int start, int finish);

main()
{
    char line[MAXLINE];

    while(getline_(line, MAXLINE) != 0) {
        reverse(line, 0, strlen(line)-2);
        fputs(line, stdout);
    }
}

int getline_(char s[], int maxline)
{
    int i, c;
    for(i=0; (c = getchar()) != EOF && c != '\n' && i < maxline; i++)
        s[i] = c;
    if (i<maxline-1 && c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

void reverse(char s[], int start, int finish)
{

    if (start >= finish)
        return;

    int temp = s[start];
    s[start] = s[finish];
    s[finish] = temp;

    reverse(s, start+1, finish-1);
}
