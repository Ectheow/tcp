#include <stdio.h>
#include <stdlib.h>
#include "sort-final.h"
#include <string.h>
#include <ctype.h>

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
void writelines(char *lines[], int nlines);

/*
 * compare_lines : string, string -> 0, 1, or -1
 * compare two lines according to sort criteria established by command
 * line arguments.
 */
int compare_lines(char *line1, char *line2);

void _qsort(void *items[], int left, int right,
	    int (*compare)(void *, void *));

#if 1
int main(int argc, char **argv)
{
    int flag_i, nlines;
    
    --argc;
    for(flag_i = 0; flag_i < MAXCOLS; flag_i++)
	flags[flag_i] = 0;
    
    for(flag_i = 0; argc > 0 && flag_i < MAXCOLS; flag_i++,--argc)
      {
	if (*(++argv)[0] == '-')
	  {
	    while (*++*argv)
	      {
		switch (**argv)
		  {
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
	  }
	else
	  {
	    printf ("Error: unrecognized argument '%s'\n", *argv);
	  }
      }

    if ((nlines = readlines(lines)) < 0)
      {
	printf("Error reading lines\n");
	return 1;
      }
    else if (nlines == 0)
      {
	return 0;
      }

    _qsort (lines, 0, nlines-1, (int (*)(void *, void *))compare_lines);
    writelines (lines, nlines);

    return 0;
}
#endif

void _qsort(void *tosort[], int left, int right,
	    int (*compare)(void *, void *))
{
  int last, i;
  void swap (void *toswap[], int l, int r);
  
  if (left >= right)
    return;

  swap (tosort, left, (left + right)/2);
  last = left;

  for (i = left+1; i <= right; i++)
    if ( (*compare) (tosort[i], tosort[left]) < 0)
      swap (tosort, i, ++last);

  swap (tosort, left, last);
  _qsort (tosort, left, last-1, compare);
  _qsort (tosort, last+1, right, compare);
}

void swap(void *toswap[], int l, int r)
{
  void *tmp;

  tmp = toswap[l];
  toswap[l] = toswap[r];
  toswap[r] = tmp;
}

void fold_line (char *in);
void directory_order_line(char *in);
int numcmp (char *in1, char *in2);
char *alloc (int size);
void dealloc (char *to_dealloc);
void lines2cols(char *in, int *ncols, char ***outcols);

int compare_lines (char *line1, char *line2)
{
  char **outcols1, **outcols2;
  int ncols1=0, ncols2=0, i, j, res;


  lines2cols (line1, &ncols1, &outcols1);
  lines2cols (line2, &ncols2, &outcols2);

  char **outcols_set[] = {
    outcols1, outcols2
  };


  for(i=0; i < min (ncols1, ncols2); i++)
    {
      for (j=0; j<2; j++)
	{
	  if (flags[i]&PROCESS_FOLD)
	    {
	      fold_line (outcols_set[j][i]);
	    }
	  if (flags[i]&PROCESS_DIRECTORY_ORDER)
	    {
	      directory_order_line (outcols_set[j][i]);
	    }
	}
      if (flags[i]&PROCESS_NUMERIC)
	{
	  if ((res = numcmp (outcols1[i], outcols2[i])) != 0)
	    {
	      goto finish;
	    }
	}
      else
	{
	  if ((res = strcmp (outcols1[i], outcols2[i])) != 0)
	    {
	      goto finish;
	    }
	}
    }

  if (ncols1 < ncols2)
    {
      res = -1;
    }
  else if (ncols1 > ncols2)
    {
      res = 1;
    }

 finish:
  for(i = 0; i<ncols1; i++)
    dealloc (outcols1[i]);
  for(i=0; i<ncols2; i++)
    dealloc (outcols2[i]);
  dealloc ( (char *)outcols1);
  dealloc ( (char *)outcols2);
  return res;
}



void lines2cols (char *in, int *ncols,
		 char ***outcols)
{
  int _ncols=0, foundword;
  char *copy, *copyp, **_outcols;

  _outcols = (char **)alloc ( (strlen (in)/2) * sizeof(char *));
  copyp = alloc (strlen (in) + 1);

  if (!copyp || !_outcols)
    {
      *ncols = -1;
      printf ("ERROR: can't alloc new memory for lines2cols\n");
      return;
    }

  strcpy (copyp, in);
  foundword = 0;
  
  while (1)
    {
      if (*copyp == '\0')
	{
	  break;
	}
      else
	{
	  if (isspace (*copyp))
	    {
	      *copyp++ = '\0';
	      foundword = 0;
	    }
	  else
	    {
	      if (!foundword)
		{
		  _outcols[_ncols++] = copyp;
		}
	      foundword = 1;
	      copyp++;
	    }
	}
    }
  *outcols = _outcols;
  *ncols = _ncols;
}

/*
 * upcase the entire line so as to have a case-insensitive sort. 
 * do it inplace, with that current memory.
 */
void fold_line(char *in)
{
  static char buf[MAXLINE];
  char *bufp = buf, *inp = in;

  while (*inp)
    {
      if (islower (*inp))
	*bufp++ = (*inp + ('A' - 'a'));
      else
	*bufp++ = *inp;
      inp++;
    }
  strcpy(in, buf);
}

void directory_order_line(char *in)
{
  static char buf[MAXLINE];
  char *inp = in, *bufp = buf;
  
  while (*inp)
    {
      if (isalnum (*inp) || isblank (*inp))
	*bufp++ = *inp;

      inp++;
    }

  strcpy(in, buf);
}

int numcmp(char *a, char *b)
{
  float af, bf;

  af = atof(a);
  bf = atof(b);


  if (af < bf)
    return -1;
  else if (af > bf)
    return 1;
  return 0;
}

#define ALLOCBUFSIZE MAXLINE*MAXLINES
static char allocbuf[MAXLINE*MAXLINES];
static char *allocp = allocbuf;

char *alloc (int to_alloc)
{
  if (allocp + to_alloc <= allocbuf + ALLOCBUFSIZE)
    {
      allocp += to_alloc;
      return allocp - to_alloc;
    }
  printf("Error! alloc out of space!\n");
  return NULL;
}

void dealloc(char *to_dealloc)
{
  if (to_dealloc >= allocbuf && to_dealloc < allocp)
    allocp = to_dealloc;
}


int _getline (char *line, int maxline);

int readlines (char *lines[])
{
  int nlines, linesize;
  char *p = NULL;
  static char staticline[MAXLINE];

  for (nlines = 0; nlines < MAXLINES
	 && (linesize = _getline (staticline, MAXLINE)) != 0;
       nlines++)
    {
      if ((p = alloc (linesize)) == NULL)
	{
	  printf ("readlines: ran out of memory\n");
	  return -1;
	}
      else
	{
	  strcpy (p, staticline);
	  lines[nlines] = p;
	}
	
    }
  return nlines;
}

int _getline (char *line, int maxline)
{
  int i, c;
  
  for (i = 0; (i < maxline-1
	       && (c = getchar ()) != EOF
	       && c != '\n');
       i++)
      line[i] = c;

  if (i < maxline-1 && c == '\n')
    line[i++] = c;

  if (i > 0)
    line[i++] = '\0';
  return i;
}


void writelines(char *lines[], int nlines)
{
  int i;

  for (i = 0; i < nlines; i++)
    printf("%s", lines[i]);
}
