#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/* entab.c: entab (retab, really) a program by replacing spaces with tabs.
 * Accepts as an argument the number of spaces per tab:
 *  $ ./entab 4 4 
 *  will replace the first two tabs with four spaces, respectively. Tabs after
 *  that are ignored.
 *  $ ./entab 2 2 3
 *  will replace the first two tabs with two spaces, and the third with three.
 *
 *  create an array of integers representing tab stops.
 *  for each line:
 *      entab the line, given the array of tab stop integers.
 *       
 * entab_line:
 * entab: 
 */

char *entab_line(char *line, int *tabstops, int ntabstops);
bool entab(char **src, char **dest, int tabstop);
int _getline(char *dst, int max);
bool is_int(char *);

#define MAXLINE 1000
#define DEFAULT_TABSTOP 4


int main(int argc, char *argv[])
{
    char line[MAXLINE];
    int tabstops[MAXLINE], ntabstops = 0;

    while(--argc > 0) {
        if (is_int(*++argv)) {
            tabstops[ntabstops++] = atoi(*argv);
        } else {
            printf("%s is not an integer!\n", *argv);
        }
    }

    while(_getline(line, MAXLINE)) {
        printf("%s", entab_line(line, tabstops, ntabstops));
    }

}

#define LINESPACE 1000
/* entab_line : string, array of tabstops, size of array -> nothing
 *
 * for each tabstop, replace that number of spaces with a tab.
 */
char *entab_line(char *line, int *tabstops, int ntabstops)
{
    static char line_space[LINESPACE];
    int i,tabstop,tabstop_i,cur_tabstop;
    char *spc_ptr = line_space;

    for(spc_ptr=line_space,cur_tabstop=0; *line != '\0'; ) {
        tabstop = tabstop_i = cur_tabstop < ntabstops ? tabstops[cur_tabstop] : DEFAULT_TABSTOP;

        for (; *line == ' ' && tabstop > 0; line++,--tabstop) 
            ;
        if (tabstop == 0) {
            *spc_ptr++ = '\t';
            cur_tabstop < ntabstops ? ++cur_tabstop : 0;
        } else {
            for(i=0; i< tabstop_i - tabstop; i++)
                *spc_ptr++ = ' ';
        }
        while(*line != ' ' && *line != '\0')
            *spc_ptr++ = *line++;
    }
    *spc_ptr = '\0';

    return line_space;
}


bool is_int(char *src)
{
    while(*src != '\0' && *src >= '0' && *src <= '9')
        src++;
    return *src == '\0';
}

int _getline(char *line, int max)
{
    int i, c;

    for(i=0; (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;

    if (i < max-1 && c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}

