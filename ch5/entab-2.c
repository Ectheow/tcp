#include <stdio.h>
#include <stdlib.h>

int is_int(char *str);
int _getline(char *line, int max);
char *entab(char *line, int start_col, int col_interval);

#define MAXLINE 1000
#define DEFAULT_START_COL 5
#define DEFAULT_COL_INTERVAL 4
int main(int argc, char *argv[])
{
    int start_col=DEFAULT_START_COL,col_interval=DEFAULT_COL_INTERVAL;
    char line[MAXLINE];

    while (--argc > 0)
        if ((*++argv)[0] != '-') {
            start_col = atoi(*argv);
        } else if ((*argv)[0] != '+') {
            col_interval = atoi(*argv);
        }  else {
            printf("Error: %s is not a sensical argument\n");
            exit(EXIT_FAILURE);
        }

    while(_getline(line, MAXLINE)) {
        printf("%s",
               entab(line, start_col, col_interval));
    }
}


char *entab(char *line, int start_col, int col_interval)
{
    static char space[MAXLINE], *spc_ptr, *tmp_line;
    int i;

    for(spc_ptr=space,i=0; i<start_col; i++)
        *spc_ptr++ = *line++;
    for(; *line != '\0'; ) {
        for(tmp_line=line; *tmp_line == ' '; tmp_line++) 
            ;
        if (tmp_line-line >= col_interval) {
            *spc_ptr++ = '\t';
            line += col_interval;
        } else {
            for (i=0; i<col_interval && *line != '\0'; i++)
                *spc_ptr++ = *line++;
        }
    }

    *spc_ptr = '\0';
    return space;
}

int _getline(char *line, int max)
{
    int i, c;
    for (i=0; (c = getchar()) != EOF && c != '\n' && i < max-1; i++)
        line[i] = c;

    if (i < max -1 && c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}
