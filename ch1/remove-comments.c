#include <stdio.h>


/* Program to strip comments from C source files */
#define NORMAL    0
#define HAD_SLASH 1
#define IN_COMMENT 2
#define HAD_STAR 3
#define FINISHED_COMMENT 4

main()
{
    int c,state;

    state = NORMAL;
    while ((c = getchar()) != EOF) {
       if (c == '/' && state == HAD_STAR) {
         state = FINISHED_COMMENT;  
       } else if(c == '/' && state == NORMAL) {
           state = HAD_SLASH;
       } else if(c == '*' && state == HAD_SLASH) {
           state = IN_COMMENT;
       } else if (c == '*' && state == IN_COMMENT) {
           state = HAD_STAR;
       }  else if (state == HAD_SLASH && c != '*') {
           putchar('/');
           state = NORMAL;
       } else if (state == HAD_STAR && c != '/') {
           state = IN_COMMENT;
       } else if (state == FINISHED_COMMENT) {
           state = NORMAL;
       }


       if (state == NORMAL)
           putchar(c);

    }
}
