#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

/* detab : remove leading tabs from a file, replacing them with a commandline
 * specified number of spaces, or a default number for each if none are
 * specified.
 *
 * program:
 *   for each line on the input:
 *     detab the line
 *
 *   detab a line:
 *     while there are leading tabs:
 *       if there is a space specification left:
 *         replace that tab with the command-line specified number of spaces
 *       else
 *         replace that tab on the output with the default number of space
 *    
 */

#define NSPACE_SPECS 100
#define MAXLINE 1000
#define DEFAULT_N_SPACE 4

char *detab_line(char *line, int *space_specs, int n_space_specs);
int _getline(char *space, int max);
bool is_int(char *num);

int main(int argc, char **argv)
{
    int space_specs[NSPACE_SPECS], n_space_specs=0;
    char line[MAXLINE];

    --argc;
    while(--argc >= 0) {
        if(!is_int(*++argv)) {
            printf("Error: %s is not an integer\n", *argv);
            exit(EXIT_FAILURE);
        } else {
            space_specs[n_space_specs++] = atoi(*argv);
        }
    }

    while(_getline(line, MAXLINE)) {
        printf("%s", 
               detab_line(line, space_specs, n_space_specs));
    }

    return 0;
}

char *detab_line(char *line, int *space_specs, int n_space_specs)
{
    static char out_space[MAXLINE], *spc_ptr, *lptr;
    int cur_space_spec, i, max;

    for (cur_space_spec=0,lptr = line,spc_ptr=out_space; *lptr != '\0'; ) {
        for (; *lptr != '\0' && *lptr == '\t'; lptr++) {
            max = cur_space_spec < n_space_specs ? space_specs[cur_space_spec++] : DEFAULT_N_SPACE;
            for(i=0; i<max; i++)
                *spc_ptr++ = ' ';
        }
        while (*lptr != '\t' && *lptr != '\0')
            *spc_ptr++ = *lptr++;
    }

    *spc_ptr = '\0';
    return out_space;
}

int _getline(char *space, int max)
{
    int i, c;

    for(i=0; (c = getchar()) != EOF &&  c != '\n' && i < max; i++)
        space[i] = c;

    if (i < max-1 && c == '\n')
        space[i++] = c;
    space[i] = '\0';

    return i;
}

bool is_int(char *num)
{
    while(isdigit(*num++))
        ;

    return *--num == '\0';
}
