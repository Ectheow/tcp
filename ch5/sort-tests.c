#include "sort-final.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 1024
#define ARRAYSZ(array) (sizeof (array) / sizeof (array[0]))

int main (int argc, char *argv[])
{
  char **outcols = NULL, buf[BUFFERSIZE];
  char *outcols_shouldbe[] = {
    "one",
    "two",
    "three",
    "four"
  };
  int ncols = 0, i;
  char *tosort[] = {
    "10",
    "1",
    "2",
    "-1",
    "31",
    "43",
    "100",
    "-2",
    "13"
  };
  int sorted[] = {
    -2,
    -1,
    1,
    2,
    10,
    13,
    31,
    43,
    100
  };

  lines2cols ("one two three four\n", &ncols, &outcols);

  if (ncols != 4)
    {
      printf ("Error! ncols: %d\n", ncols);
    }
  else
    {
      printf ("OK\n");
    }
  for (i=0; i < min (ARRAYSZ (outcols_shouldbe), ncols); i++)
    {
      if (strcmp (outcols[i], outcols_shouldbe[i]))
	{
	  printf ("Error! outcols %d is %s, should be %s\n",
		 i, outcols[i], outcols_shouldbe[i]);
	}
    }

  strcpy (buf, "aAbBcE");
  fold_line (buf);
  if (strcmp (buf, "AABBCE"))
    {
      printf("Error! %s is not a folded line\n");
    }
  else
    {
      printf("OK fold\n");
    }

  strcpy(buf, "@@aA@@()\n b");
  directory_order_line(buf);
  if (strcmp (buf, "aA b"))
    {
      printf("Error! %s is not a directory-order line\n");
    }
  else
    {
      printf("OK directory-order\n");
    }

  
  int n;

  _qsort (tosort, 0, ARRAYSZ (tosort)-1, (int (*)(void *, void *))numcmp);
  for (i = 0; i < ARRAYSZ (tosort); i++)
    {
      n = atoi (tosort[i]);
      if (n != sorted[i])
	{
	  printf ("Error! index %d: %d != %d\n",
		 i, n, sorted[i]);
	}
      else
	{
	  printf ("index %d %d == %d OK\n", i, sorted[i], atoi(tosort[i]));
	}
    }
  return 0;
}
