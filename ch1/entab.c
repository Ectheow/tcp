#include <stdio.h>

/* entab a program - 
 * replace consecutive blanks on input with a tab, if and when there are enough
 * of them.
 */

#define TAB_STOP 8
#define NOT_SPACE 0
#define SPACE 1

main()
{
    int c,state,n_spcs,i;

    state = NOT_SPACE;
    n_spcs = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ') {
            state = SPACE;
            ++n_spcs;
        } else if (c == '\t') {
            state = SPACE;
            n_spcs += TAB_STOP;   
        } else {
            state = NOT_SPACE;
            for(i=n_spcs/TAB_STOP; i > 0; --i) 
                putchar('\t');
            for(i = n_spcs%TAB_STOP; i> 0; --i) 
                putchar(' ');
            n_spcs = 0;
            putchar(c);
        }
    return 0;
}
