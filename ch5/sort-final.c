#include <stdio.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXLINE 1000
#define MAXCOLS 500

#define PROCESS_FOLD 0x1
#define PROCESS_DIRECTORY_ORDER 0x2
#define PROCESS_NUMERIC 0x04

int flags[MAXCOLS];
char *lines[MAXLINES];
/*
 * readlines: array of strings -> number
 * read lines in from stdin, and return the number of lines read.
 */
int readlines(char *lines[]);

/*
 * writelines: array of strings -> nothing
 * write the lines in lines out to stdout.
 */
void writelines(char *lines[]);

int compare_lines(char *line1, char *line2);
void _qsort(void *items[], int left, int right,
	    int (*compare)(void *, void *));

int main(int argc, char **argv)
{
    int flag_i, nlines;
    
    --argc;
    for(flag_i = 0; flag_i < MAXCOLS; flag_i++)
	flags[flag_i] = 0;
    
    for(flag_i = 0; argc >= 0 && flag_i < MAXCOLS; flag_i++,--argc) {
	if (*(++argv)[0] == '-') {
	    while (*++*argv) {
		switch (**argv) {
		case 'n':
		    flags[flag_i] |= PROCESS_NUMERIC;
		    break;
		case 'd':
		    flags[flag_i] |= PROCESS_DIRECTORY_ORDER;
		    break;
		case 'f':
		    flags[flag_i] |= PROCESS_FOLD;
		    break;
		default:
		    printf("Error: unrecognized option '%c'\n", **argv);
		    break;
		}
	    }
	} else {
	    printf("Error: unrecognized argument '%s'\n", *argv);
	}
    }

    if ((nlines = readlines(lines)) < 0) {
    } else if (nlines == 0) {
	return 0;
    }

    _qsort(lines, 0, nlines-1, (int (*)(void *, void *))compare_lines);
    writelines(lines, nlines);

    return 0;
}

void fold_line(char *in);
void directory_order_line(char *in);
int numcmp(char *in1, char *in2);

void lines2cols(char *in, int *ncols, char ***outcols);

int compare_lines(char *line1, char *line2) {
    char **outcols1, **outcols2;
    int ncols1=0, ncols2=0, i;


    lines2cols(line1, &ncols1, &outcols1);
    lines2cols(line2, &ncols2, &outcols2);



    char **outcols_set[] = {
	outcols1, outcols2
    };


    for(i=0; i<min(ncols1, ncols2); i++) {
	for (j=0; j<2; j++) {
	    if(flags[i]&PROCESS_FOLD) {
		fold_line(outcols_set[j][i]);
	    }
	    if (flags[i]&PROCESS_DIRECTORY_ORDER) {
		directory_order_line(outcols_set[j][i]);
	    }
	}
	if (flags[i]&PROCESS_NUMERIC) {
	    if ((res = numcmp(outcols1[i], outcols2[i])) != 0) {
		return res;
	    }
	} else {
	    if ((res = strcmp(outcols1[i], outcols2[i])) != 0) {
		return res;
	    }
	}
    }

    if (ncols1 < ncols2) {
	return -1;
    } else if (ncols1 > ncols2) {
	return 1;
    }

    return 0;
}

int ncols(char *in)
{
    int i, ncols;
    for(ncols=0,i=0; i<strlen(in); i++) {
	if (isspace(in[i]))
	    ncols++;
	while(in[i] && isspace(in[i]))
	    i++;
    }
    return ncols;
}

void lines2cols(char *in, int *ncols, char ***outcols)
{
    int _ncols;

    _ncols = ncols(in);

}
