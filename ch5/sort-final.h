#ifndef _SORT_FINAL_H_
#define _SORT_FINAL_H_

void lines2cols (char *in, int *ncols, char ***outcols);
void directory_order_line (char *in);
void fold_line (char *in);
void _qsort (void *v[], int, int, int (*)(void *, void *));
int numcmp (char *, char *);
#define min(a, b) ( (a) < (b) ? (a) : (b) )
#endif
