#include <stdio.h>

int atoi(char s[]);
int lower(int c);
int tolower(char s[]);
int add(char line[]);

main()
{
    int quit=0,c=0;

    while(!quit) {
        if((func = getchar()) == EOF)
            quit = 1;
        else {
            if(getline(line, MAXLINE) == 0)
                quit = 1;
            else if (func == 'l') {
                tolower(line);
                printf("%s", line);
            } else if(func == 'a') {
                add(line);
                printf("%s", line);
            }
        }
    }
}
